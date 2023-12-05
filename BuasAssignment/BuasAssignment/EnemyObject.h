#pragma once
#include "GameObject.h"

class EnemyObject : public GameObject
{
public:
	explicit EnemyObject(Game* game);

	void Start() override;
	void Update(float deltaTime) override;
	

private:
	float _enemySpeed = 75.f;
	bool _moveLeft = true;
	float _moveDirection = -1.f;
};

