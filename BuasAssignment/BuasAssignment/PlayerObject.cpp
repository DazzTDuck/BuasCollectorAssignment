#include "PlayerObject.h"
#include <iostream>
#include "EnemyObject.h"
#include "Game.h"
#include "MathFunctions.h"

PlayerObject::PlayerObject(Game* game) :
	GameObject(game),
	_idleAnimation(4, 96, 80, 0),
	_runAnimation(8, 96, 80, 0),
	_jumpAnimation(2, 96, 80, 0),
	_attackAnimation(8, 96, 80, 0),
	_deathAnimation(8, 96, 80, 0)
{
	//load all textures
	_idleTexture.loadFromFile("Assets/Character/Idle/Idle-Sheet.png");
	_runTexture.loadFromFile("Assets/Character/Run/Run-Sheet.png");
	_jumpTexture.loadFromFile("Assets/Character/Jump-All/Jump-All-Sheet.png");
	_attackTexture.loadFromFile("Assets/Character/Attack-01/Attack-01-Sheet.png");
	_deathTexture.loadFromFile("Assets/Character/Dead/Dead-Sheet.png");

	//setup sprite texture
	_sprite.setTexture(_idleTexture);
	_sprite.setTextureRect({ 0, 0, 96, 80 });

	//sprite values
	_sprite.setPosition(objectPosition);
	_sprite.setScale(objectScale);
	_spriteCorrectionOffset = { -28.f, 6.f };

	//make collider shape and size
	_collider.setSize({ 21 * objectScale.x, 48 * objectScale.y});
	_collider.setOutlineColor(sf::Color::White);
	_collider.setOutlineThickness(colliderDrawThickness);
	_collider.setFillColor(sf::Color::Transparent);

	//setup origin
	spriteOrigin = { _collider.getGlobalBounds().width * 0.4f, _collider.getGlobalBounds().height * 0.45f };

	_originalOrigin = spriteOrigin;
	_sprite.setOrigin(spriteOrigin);

	//creating hitbox
	_hitBox.setSize({ 10.f, 30.f });
	_hitBox.setOutlineColor(sf::Color::White);
	_hitBox.setOutlineThickness(colliderDrawThickness);
	_hitBox.setFillColor(sf::Color::Transparent);

	//offsetting player hitbox
	_hitBoxOffset = { 25.f , 10.f};

	//set start location
	objectPosition = { 300.f, 250.f }; //set start position
	respawnLocation = objectPosition;

	//physics values
	_objectDrag = 0.8f;
	_hasGravity = true;

	//object properties
	objectName = "Player";
	objectMass = 1.5f;
	objectType = PLAYER;
	hitPoints.SetHitPoints(3);

	//debug bounding box
	//drawCollider = true;
}

void PlayerObject::Start()
{
	//1 second delay before player can do anything
	_actionActive = true;
	_actionDelay = 0.f;
	_currentDelay = 1.f;
}

void PlayerObject::Draw(sf::RenderWindow& window)
{
	if(drawCollider)
		window.draw(_hitBox);

	GameObject::Draw(window);
}

void PlayerObject::Update(float deltaTime)
{
	//player movement
	float moveX = 0.f;

	if (Input::GetInput(sf::Keyboard::A))
		moveX -= 1.f; //left
	if (Input::GetInput(sf::Keyboard::D))
		moveX += 1.f; //right

	//apply player movement force
	if (!_attacking && !_isDead)
	{
		float forceX = moveX * (_grounded ? 1.f : 0.5f) * _playerSpeed; //if not grounded move slower
		float speedPercent = 1 - MathFunctions::Clamp01(abs(_velocity.x) / _maxMoveVelocity);

		ApplyForce({forceX / objectMass * speedPercent, 0.0f }, deltaTime);
	}

	//jumping input
	if (Input::GetInput(sf::Keyboard::Space) && !_actionActive && _grounded && !_isDead)
	{
		float jumpVelocity = -sqrt(2 * GRAVITY * objectMass * _jumpHeight);

		sf::Vector2f force(0.f, 0.f);
		force.y = jumpVelocity / _jumpTime;

		ApplyForce(force, deltaTime);

		_actionActive = true;
		_actionDelay = 0.f;
		_currentDelay = _jumpReactivateDelay;

		PlaySound("Jump", 25.f);
	}

	//attack input
	if (Input::GetInput(sf::Keyboard::E) && !_actionActive && !_attacking && !_isDead && _grounded)
	{
		_attacking = true;
		_hasAttacked = false;
		_actionActive = true;
		_actionDelay = 0.f;
		_currentDelay = _attackDelay;

		PlaySound("Swing", 25.f);
	}

	//handle animation & texture swapping
	if (_isDead)
	{
		if (_deathAnimation.PlayAnimation(_sprite, deltaTime))
			_sprite.setTexture(_deathTexture);
	}
	else if (_attacking) 
	{
		if (_attackAnimation.PlayAnimation(_sprite, deltaTime))
			_sprite.setTexture(_attackTexture);
	}
	else if (!_grounded)
	{
		if (_jumpAnimation.PlayAnimation(_sprite, deltaTime))
			_sprite.setTexture(_jumpTexture);
	}
	else if (abs(_velocity.x) > 0.05f)
	{
		if (_runAnimation.PlayAnimation(_sprite, deltaTime))
			_sprite.setTexture(_runTexture);
	}
	else if (abs(_velocity.x) < 0.05f)
	{
		if (_idleAnimation.PlayAnimation(_sprite, deltaTime))
			_sprite.setTexture(_idleTexture);
	}

	//handle flipping of sprite based on movement speed
	FlipSprite(1.f, 0.9f);

	//make hitbox follow player, reverse X when flipped
	_hitBox.setPosition(objectPosition + sf::Vector2f{ (_isFlipped ? -_hitBoxOffset.x * 0.55f : _hitBoxOffset.x), _hitBoxOffset.y });

	//handle collisions
	GameObjectColliding(deltaTime);

	GameObject::Update(deltaTime); //rest of the GameObject update function

	//timed delay value
	if (_actionActive)
		_actionDelay += deltaTime;

	//reset action trigger
	if (_actionDelay >= _currentDelay && _actionActive)
	{
		if (_attacking)
		{
			//reset attacking action
			if (_currentDelay >= _attackDelay && _attackAnimation.GetAnimationStep() % 4 == 0) 
			{
				_attacking = false;

				_actionDelay = 0.f;
				_currentDelay = 0.f;
				_actionActive = false;
			}
			return;
		}

		if(_isDead) 
		{
			//player is dead
			_game->ResetGame();
			_isDead = false;
		}

		//other actions 
		_actionDelay = 0.f;
		_currentDelay = 0.f;
		_actionActive = false;
	}

	CheckOutOfBounds(_game->gameWindow);
}

void PlayerObject::GameObjectColliding(float deltaTime)
{
	//set head point
	_pointHead = (objectPosition + sf::Vector2f(_collider.getGlobalBounds().width / 2, -5.f));

	for (auto tileObject : _game->collisionTiles)
	{
		if (!_grounded)
		{
			sf::FloatRect tileBounds = tileObject->GetSprite()->getGlobalBounds();

			//if colliding with something above, reverse velocity
			if (MathFunctions::IsPointInBounds(_pointHead, tileBounds))
			{
				SetVelocityY(-_velocity.y / 2); // if you hit a ceiling, bounce player back down
			}
		}
	}

	//player colliding with other game objects
	for (auto& object : _game->objectsList)
	{
		if (object.second == this || object.second->isDisabled)
			continue;

		switch (object.second->objectType)
		{
			case COIN: //Coin collecting
				{
					if (MathFunctions::AreBoundsColliding(_collider.getGlobalBounds(), object.second->GetBounds(), _overlapCollision))
					{
						_coinsCollected++;
						object.second->isDisabled = true;

						_game->userInterface->UpdateCoinsText(_coinsCollected, _maxCoins);
						PlaySound("Collect", 20.f);
					}
				}
				break;
			case CHEST: //Colliding with ending chest
				{
					if(_coinsCollected != _maxCoins)
						continue;

					_game->userInterface->gameCompleted = MathFunctions::AreBoundsColliding(_collider.getGlobalBounds(), object.second->GetBounds(), _overlapCollision);

					if (_game->userInterface->gameCompleted && Input::GetInput(sf::Keyboard::R))
					{
						_game->ResetGame();
					}
				}
				break;
			case ENEMY: //colliding with enemy types
				{
					if (_attacking && !_hasAttacked && object.second->hitPoints.GetCurrentHitPoints() != 0)
					{
						//only attack second last frame in swings
						if (_attackAnimation.GetAnimationStep() == 3 || _attackAnimation.GetAnimationStep() == 7)
						{
							if (MathFunctions::AreBoundsColliding(_hitBox.getGlobalBounds(), object.second->GetBounds(), _overlapCollision))
							{
								object.second->hitPoints.RemoveHitPoint();

								//push enemy back a bit in the direction you hit it
								object.second->ApplyImpulse({ MathFunctions::Normalize(object.second->objectPosition - objectPosition).x * 250.f, 0.f }, deltaTime);
								_hasAttacked = true;

								object.second->PlaySound("EnemyHit", 20.f);

								return; //make sure player does not take damage in same frame as hitting enemy
							}
						}
					}

					//do damage to player
					if (MathFunctions::AreBoundsColliding(_collider.getGlobalBounds(), object.second->GetBounds(), _overlapCollision) && !_isDead && !_actionActive && object.second->hitPoints.GetCurrentHitPoints() != 0)
					{
						hitPoints.RemoveHitPoint();

						//update UI
						_game->userInterface->UpdateHearts(hitPoints.GetCurrentHitPoints());

						_actionActive = true;
						_actionDelay = 0.f;

						_isDead = hitPoints.GetCurrentHitPoints() == 0;
						_currentDelay = _isDead ? _deathDelay : _hitDelay;

						ApplyImpulse({ -MathFunctions::Normalize(object.second->objectPosition - objectPosition).x * _playerGetDamageKnockBack, 0.f }, deltaTime);

						PlaySound("PlayerHit", 25.f);
					}
				}
				break;
		}
	}
}

void PlayerObject::OnRespawn()
{
	GameObject::OnRespawn();

	_coinsCollected = 0;

	//reset text UI
	_game->userInterface->UpdateCoinsText(_coinsCollected, _maxCoins);
	_game->userInterface->gameCompleted = false;

	//reset animations
	hitPoints.ResetHitPoints();
	_idleAnimation.ResetAnimation();
	_runAnimation.ResetAnimation();
	_jumpAnimation.ResetAnimation();
	_attackAnimation.ResetAnimation();
	_deathAnimation.ResetAnimation();
}

void PlayerObject::CoinAdded()
{
	_maxCoins++;

	//update UI
	_game->userInterface->UpdateCoinsText(_coinsCollected, _maxCoins);
}

void PlayerObject::CheckOutOfBounds(sf::RenderWindow& window)
{
	sf::FloatRect bounds = _sprite.getGlobalBounds();

	//if player falling down, reset game
	if (objectPosition.y + bounds.height > window.getSize().y && !_isDead)
	{		
		_game->ResetGame();
	}
}
