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

	float _enemySpeed;
	bool _moveLeft = true;
	float _moveDirection = -1.f;

	float _deathDelay = 1.25f;
	float _deathTime = 0.f;
	bool _stopDeathAnimation = false;

	Animations _moveAnimation;
	Animations _deathAnimation;
	Animations _idleAnimation;

private:
	Animations _unhideAnimation;

	bool _hidden = true;
	bool _canShow = true;
	float _sqrDistance = 250.f * 250.f; // 250 pixels
};

