#include "BoarEnemy.h"

#include <iostream>

BoarEnemy::BoarEnemy(Game* game):
	EnemyObject(game)
{
	_idleAnimation = Animations(4, 48, 32, 32);
	_deathAnimation = Animations(4, 48, 32, 32);
	_moveAnimation = Animations(6, 48, 32, 32);

	//set texture
	_defaultTexture.loadFromFile("Assets/Mob/Boar/boar-brown-all.png");
	_sprite.setTexture(_defaultTexture);
	_sprite.setTextureRect({ 0, 32, 48, 32});

	//set collider size
	_collider.setSize({ 22.f * objectScale.x, 22.f * objectScale.y });

	//set origin
	spriteOrigin = { _sprite.getGlobalBounds().width * 0.3f, _sprite.getGlobalBounds().width * 0.2f };
	_originalOrigin = spriteOrigin;
	_sprite.setOrigin(spriteOrigin);

	//object properties
	objectName = "Boar";
	objectType = ENEMY;
	_enemySpeed = 35.f;
	objectMass = 1.35f;
	hitPoints.SetHitPoints(1);

	//physics properties
	_objectDrag = 0.91f;
	_hasGravity = true;

	//debug bounding box
	drawCollider = true;
}

void BoarEnemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	_idleAnimation.PlayAnimation(_sprite, deltaTime);
}

void BoarEnemy::OnRespawn()
{
	GameObject::OnRespawn();

	hitPoints.ResetHitPoints();
	_sprite.setTextureRect({ 288, 32, 48, 32 });
	_deathTime = 0.f;
	_moveDirection = -1;

	_idleAnimation.ResetAnimation();
	_moveAnimation.ResetAnimation();
	_deathAnimation.ResetAnimation();
}
