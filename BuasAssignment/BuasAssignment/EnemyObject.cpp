#include "EnemyObject.h"
#include "Game.h"
#include "MathFunctions.h"

EnemyObject::EnemyObject(Game* game):
	GameObject(game),
	_moveAnimation(8, 48, 32, 0),
	_deathAnimation(8, 48, 32, 96),
	_idleAnimation(8, 48, 32, 32),
	_unhideAnimation(8, 48, 32, 64)
{
	//set texture
	_defaultTexture.loadFromFile("Assets/Mob/Snail/all.png");
	_sprite.setTextureRect({288, 32, 48, 32});

	//set collider size
	_collider.setSize({22.f * objectScale.x, 22.f * objectScale.y});

	//set origin
	spriteOrigin = { _sprite.getGlobalBounds().width * 0.3f, _sprite.getGlobalBounds().width * 0.2f };
	_originalOrigin = spriteOrigin;
	_sprite.setOrigin(spriteOrigin);

	//set starting position
	objectPosition = {1400.f, 300.f};
	respawnLocation = objectPosition;

	//object properties
	objectName = "Snail";
	objectType = ENEMY;
	_enemySpeed = 25.f;
	objectMass = 1.2f;
	hitPoints.SetHitPoints(1);

	//physics properties
	_objectDrag = 0.91f;
	_hasGravity = true;

	//debug bounding box
	//drawCollider = true;
}

void EnemyObject::Start()
{
}

void EnemyObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if(hitPoints.GetCurrentHitPoints() == 0) //enemy is dead
	{
		if(!_stopDeathAnimation)
			_deathAnimation.PlayAnimation(_sprite, deltaTime);

		if (_deathAnimation.HasLastFramePlayed()) //on last frame stop animating
			_stopDeathAnimation = true;

		_deathTime += deltaTime;

		if(_deathTime > _deathDelay && _stopDeathAnimation) //remove enemy after certain time
		{
			_deathAnimation.ResetAnimation();
			_stopDeathAnimation = false;

			isDisabled = true; //disable enemy
		}

		return;
	}

	float distance = MathFunctions::GetSqrDistance(objectPosition, _game->objectsList["player"]->objectPosition);

	if (_hidden && _canShow)
	{
		//unhide snail
		_unhideAnimation.PlayAnimation(_sprite, deltaTime);

		if (_unhideAnimation.HasLastFramePlayed()) //on last frame
		{
			_hidden = false;
			_unhideAnimation.ResetAnimation();
			_idleAnimation.ResetAnimation();
		}

	}

	if(distance < _sqrDistance)
	{
		_canShow = true;
		if(!_hidden)
		{
			//play moving animation
			_moveAnimation.PlayAnimation(_sprite, deltaTime);

			//reset animation
			_idleAnimation.ResetAnimation();

			if (_moveAnimation.GetAnimationStep() > 4)
				MoveSideToSide(deltaTime); //actually move enemy
		}
	}
	else
	{
		if(_canShow)
		{
			_hidden = false;
			_canShow = false;
			_idleAnimation.ResetAnimation();
		}

		//hide snail if player is too far away
		if(!_hidden)
		{
			_idleAnimation.PlayAnimation(_sprite, deltaTime);

			if(_idleAnimation.HasLastFramePlayed())
			{
				_unhideAnimation.ResetAnimation();
				_idleAnimation.ResetAnimation();
				_hidden = true;
			}
		}
	}

	//flip sprite functionality
	if(hitPoints.GetCurrentHitPoints() != 0)
		FlipSprite(1.f, 0.8f, true);
}

void EnemyObject::OnRespawn()
{
	GameObject::OnRespawn();

	_hidden = true;
	hitPoints.ResetHitPoints();
	_sprite.setTextureRect({ 288, 32, 48, 32 });
	_deathTime = 0.f;
	_moveDirection = -1;
	_moveLeft = true;

	_idleAnimation.ResetAnimation();
	_unhideAnimation.ResetAnimation();
	_moveAnimation.ResetAnimation();
	_deathAnimation.ResetAnimation();
}

float EnemyObject::GetCurrentMoveDirection() const
{
	return _moveDirection;
}

void EnemyObject::MoveSideToSide(float deltaTime)
{
	if (!_leftPointGrounded && _moveLeft)
	{
		_moveLeft = false;
		_moveDirection = -_moveDirection;
	}
	else if (!_rightPointGrounded && !_moveLeft)
	{
		_moveLeft = true;
		_moveDirection = -_moveDirection;
	}

	if (_grounded)
	{
		SetVelocityX(_moveDirection * _enemySpeed * deltaTime);
	}
}

