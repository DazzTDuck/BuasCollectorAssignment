#include "EnemyObject.h"

#include <iostream>

EnemyObject::EnemyObject(Game* game):
	GameObject(game)
{
	_defaultTexture.loadFromFile("Assets/Mob/Snail/walk-Sheet.png");

	_sprite.setTextureRect({ 0, 0, 48, 32});

	//reset collider
	_collider.setSize(_sprite.getGlobalBounds().getSize());

	objectPosition = { 1400.f, 300.f };
	respawnLocation = objectPosition;

	objectName = "Snail";
	objectMass = 1.2f;
	_hasGravity = true;

	drawCollider = true;
}

void EnemyObject::Start()
{
	
}

void EnemyObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (!_leftPointGrounded && _moveLeft)
	{
		_moveLeft = false;
		_moveDirection = -_moveDirection;
	}
	else if(!_rightPointGrounded && !_moveLeft)
	{
		_moveLeft = true;
		_moveDirection = -_moveDirection;
	}

	if(_grounded)
		SetVelocityX(_moveDirection * _enemySpeed * deltaTime);

	FlipSprite(2.f, 1.f, true);
}

