#pragma once
#include "Animations.h"
#include "GameObject.h"
#include "HitPoints.h"

class EnemyObject : public GameObject
{
public:
	explicit EnemyObject(Game* game);

	void Start() override;
	void Update(float deltaTime) override;
	void OnRespawn() override;
	float GetCurrentMoveDirection() const;

	HitPoints hitPoints;

protected:
	virtual void MoveSideToSide(float deltaTime);

	float _enemySpeed;
	bool _moveLeft = true;
	float _moveDirection = -1.f;

	float _deathDelay = 1.25f;
	float _deathTime = 0.f;
	bool _stopDeathAnimation = false;

	Animations _moveAnimation;
	Animations _deathAnimation;

private:
	Animations _hideAnimation;
	Animations _unhideAnimation;

	bool _hidden = true;
	float _sqrDistance = 500.f * 500.f; // 500 pixels
};

