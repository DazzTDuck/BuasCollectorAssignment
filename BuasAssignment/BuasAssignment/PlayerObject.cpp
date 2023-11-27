#include "PlayerObject.h"
#include <iostream>
#include "Game.h"
#include "MathFunctions.h"

PlayerObject::PlayerObject(Game* game):
	GameObject(game),
	_idleTexture(),
	_runTexture(),
	_jumpTexture(),
	_idleAnimation(4),
	_runAnimation(8),
	_jumpAnimation(2)
{
	_idleTexture.loadFromFile("Assets/Character/Idle/Idle-Sheet.png");
	_runTexture.loadFromFile("Assets/Character/Run/Run-Sheet.png");
	_jumpTexture.loadFromFile("Assets/Character/Jump-All/Jump-All-Sheet.png");

	_sprite.setTexture(_idleTexture);
	_sprite.setTextureRect({ 22, 16, 35, 48 });
	_sprite.setPosition(objectPosition);
	_sprite.setScale(objectScale);
	spriteOrigin = _sprite.getOrigin();

	//make collider shape & resize it
	_collider.setSize(_sprite.getGlobalBounds().getSize() - sf::Vector2f{ 30.f, 0.f });
	_collider.setOutlineColor(sf::Color::White);
	_collider.setOutlineThickness(colliderDrawThickness);
	_collider.setFillColor(sf::Color::Transparent);

	objectPosition = { 300.f, 100.f }; //set start position
	respawnLocation = objectPosition;
	_objectDrag = 0.9f;

	_hasGravity = true;
	objectName = "Player";
}

void PlayerObject::Start()
{
}


void PlayerObject::Update(float deltaTime)
{
	//player movement
	float moveX = 0.f;

	if (Input::GetInput(sf::Keyboard::A))
		moveX -= 1.f; //left
	if (Input::GetInput(sf::Keyboard::D))
		moveX += 1.f; //right

	SetVelocityX(moveX * _playerSpeed * deltaTime);

	//jumping
	if (Input::GetInput(sf::Keyboard::Space) && !_jumped)
	{
		float jumpVelocity = -sqrt(2 * GRAVITY * _jumpHeight);

		sf::Vector2f force(0.f, 0.f);
		force.y = objectMass * jumpVelocity / _jumpTime;

		ApplyForce(force, deltaTime, true);

		_jumped = true;
		_jumpDelay = 0.f;

		PlaySound("Jump", 25.f);
	}

	//handle animation & texture swapping
	if(!_grounded)
	{
		if (_jumpAnimation.PlayAnimation("PlayerJumpAir", _sprite, deltaTime))
			_sprite.setTexture(_jumpTexture);
	}
	else if (abs(_velocity.x) > 0.f)
	{
		if(_runAnimation.PlayAnimation("PlayerRun", _sprite, deltaTime))
			_sprite.setTexture(_runTexture);
	}
	else if (abs(_velocity.x) == 0.f)
	{
		if(_idleAnimation.PlayAnimation("PlayerIdle", _sprite, deltaTime))
			_sprite.setTexture(_idleTexture);
	}

	//handle flipping of sprite based on movement speed
	FlipSprite(2.f);

	GameObjectColliding();

	GameObject::Update(deltaTime); //rest of the GameObject update function

	//timed delay value
	if (_jumped)
		_jumpDelay += deltaTime;

	//reset jump trigger
	if(_jumpDelay >= _jumpReactivateDelay && _jumped)
	{
		_jumpDelay = 0.f;
		_jumped = false;
	}

	CheckOutOfBounds(_game->gameWindow);
}

void PlayerObject::GameObjectColliding()
{
	//player colliding with other game objects
	for (auto object : _game->objectsList)
	{
		if(object.second == this || object.second->isDisabled)
			continue;

		if (MathFunctions::AreBoundsColliding(_collider.getGlobalBounds(), object.second->GetBounds(), _overlapCollision))
		{
			if (MathFunctions::SqrMagnitude(_overlapCollision) > _minSqrCollisionOverlap)
			{
				if (object.second->objectName == "Coin")
				{
					_coinsCollected++;
					object.second->isDisabled = true;

					PlaySound("Collect", 20.f);
				}
			}
		}
	}
}

void PlayerObject::CheckOutOfBounds(sf::RenderWindow& window)
{
	sf::FloatRect bounds = _sprite.getGlobalBounds();

	//todo use SFML view (https://www.sfml-dev.org/tutorials/2.5/graphics-view.php)

	if (objectPosition.x + bounds.width > window.getSize().x * 0.8 || objectPosition.x < 256)
	{
		float value = objectPosition.x > 256 ? -5.16f : 5.16f;

		//move all tiles & objects
		for (auto tile : _game->activeTiles)
		{
			tile->GetSprite()->move({ value, 0.f });
		}

		for (auto gameObject : _game->objectsList)
		{
			gameObject.second->objectPosition += {value, 0.f};
		}
	}

	//if player falling down, reset game
	if (objectPosition.y + bounds.height > window.getSize().y)
	{
		_coinsCollected = 0;

		//respawn and reset all objects
		for (auto gameObject : _game->objectsList)
		{
			gameObject.second->isDisabled = false;
			gameObject.second->objectPosition = gameObject.second->respawnLocation;
			gameObject.second->SetVelocity({ 0.f, 0.f }); //reset velocity
		}

		//reset all tile position
		for (auto tile : _game->activeTiles)
		{
			tile->GetSprite()->setPosition(tile->startPosition);
		}
	}
}
