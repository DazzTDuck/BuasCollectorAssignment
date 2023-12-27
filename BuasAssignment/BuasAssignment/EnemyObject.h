#pragma once
#include "Animations.h"
#include "GameObject.h"

class EnemyObject : public GameObject
{
public:
	explicit EnemyObject(Game* game);

	void Start() override;
	void Update(float deltaTime) override;
	void OnRespawn() override;
	float GetCurrentMoveDirection() const;

protected:
	virtual void MoveSideToSide(float deltaTime);

	float _enemySpeed = 1.f;
	bool _moveLeft = true;
	float _moveDirection = -1.f;

	float _deathDelay = 1.25f;
	float _deathTime = 0.f;
	bool _stopDeathAnimation = false;

	Animations _moveAnimation;
	Animations _deathAnimation;
	Animations _idleAnimation;
};

