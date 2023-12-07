#include "EnemyObject.h"
#include "Game.h"
#include "MathFunctions.h"

EnemyObject::EnemyObject(Game* game):
	GameObject(game),
	hitPoints(1),
	_moveAnimation(8, 48, 32, 0),
	_deathAnimation(8, 48, 32, 96),
	_hideAnimation(8, 48, 32, 32),
	_unhideAnimation(8, 48, 32, 64)
{
	_defaultTexture.loadFromFile("Assets/Mob/Snail/all.png");

	_sprite.setTextureRect({288, 32, 48, 32});

	//reset collider
	//_collider.setSize(_sprite.getGlobalBounds().getSize());
	_collider.setSize({45.f, 45.f});
	spriteOrigin = { _sprite.getGlobalBounds().width * 0.15f, _sprite.getGlobalBounds().width * 0.1f };

	_originalOrigin = spriteOrigin;
	objectPosition = {1400.f, 300.f};
	respawnLocation = objectPosition;

	objectName = "Snail";
	objectType = ENEMY;
	_enemySpeed = 100.f;
	objectMass = 1.2f;
	_objectDrag = 0.91f;
	_hasGravity = true;

	drawCollider = true;
}

void EnemyObject::Start()
{
}

void EnemyObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (isDisabled)
		return;

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

	if(MathFunctions::GetSqrDistance(objectPosition, _game->objectsList["player"]->objectPosition) < _sqrDistance)
	{
		if (_hidden)
		{
			//unhide snail
			_unhideAnimation.PlayAnimation(_sprite, deltaTime);

			if (_unhideAnimation.HasLastFramePlayed()) //on last frame
			{
				_hidden = false;
				_unhideAnimation.ResetAnimation();
			}
				
		}
		else
		{
			//play moving animation
			_moveAnimation.PlayAnimation(_sprite, deltaTime);

			if (_moveAnimation.GetAnimationStep() > 4)
				MoveSideToSide(deltaTime); //actually move enemy
		}
	}
	else
	{
		//hide snail if player is too far away
		if(!_hidden)
		{
			_hideAnimation.PlayAnimation(_sprite, deltaTime);

			if (_hideAnimation.HasLastFramePlayed()) //on last frame
			{
				_hidden = true;
				_hideAnimation.ResetAnimation();
			}
		}
	}

	//flip sprite functionality
	if(hitPoints.GetCurrentHitPoints() != 0)
		FlipSprite(2.f, 0.8f, true);
}

void EnemyObject::OnRespawn()
{
	GameObject::OnRespawn();

	_hidden = true;
	hitPoints.ResetHitPoints();
	_sprite.setTextureRect({ 288, 32, 48, 32 });
	_deathTime = 0.f;

	_hideAnimation.ResetAnimation();
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

