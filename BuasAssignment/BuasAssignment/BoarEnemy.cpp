#include "BoarEnemy.h"

#include <iostream>

BoarEnemy::BoarEnemy(Game* game):
	EnemyObject(game)
{
	_idleAnimation = Animations(4, 48, 32, 32);
	_deathAnimation = Animations(4, 48, 32, 0);
	_moveAnimation = Animations(6, 48, 32, 64);

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
	_enemySpeed = 80.f;
	objectMass = 1.35f;
	hitPoints.SetHitPoints(1);
	_deathDelay = 0.7f;

	//physics properties
	_objectDrag = 0.91f;
	_hasGravity = true;

	//debug bounding box
	//drawCollider = true;
}

void BoarEnemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (hitPoints.GetCurrentHitPoints() == 0) //enemy is dead
	{
		if (!_stopDeathAnimation)
			_deathAnimation.PlayAnimation(_sprite, deltaTime);

		if (_deathAnimation.HasLastFramePlayed()) //on last frame stop animating
			_stopDeathAnimation = true;

		_deathTime += deltaTime;

		if (_deathTime > _deathDelay && _stopDeathAnimation) //remove enemy after certain time
		{
			_deathAnimation.ResetAnimation();
			_stopDeathAnimation = false;

			isDisabled = true; //disable enemy
		}

		return;
	}

	_moveAnimation.PlayAnimation(_sprite, deltaTime);
	MoveSideToSide(deltaTime);

	//flip sprite functionality
	if (hitPoints.GetCurrentHitPoints() != 0)
		FlipSprite(1.f, 0.7f, true);
}
