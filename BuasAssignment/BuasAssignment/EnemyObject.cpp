#include "EnemyObject.h"
#include "Game.h"
#include "MathFunctions.h"

EnemyObject::EnemyObject(Game* game):
	GameObject(game),
	_moveAnimation(8, 48, 32, 0),
	_deathAnimation(8, 48, 32, 96),
	_idleAnimation(8, 48, 32, 32)
{
}

void EnemyObject::Start()
{
}

void EnemyObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void EnemyObject::OnRespawn()
{
	GameObject::OnRespawn();

	hitPoints.ResetHitPoints();
	_sprite.setTextureRect({ 288, 32, 48, 32 });
	_deathTime = 0.f;
	_moveDirection = -1;
	_moveLeft = true;

	_idleAnimation.ResetAnimation();
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

