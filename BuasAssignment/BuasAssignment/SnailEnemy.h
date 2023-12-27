#pragma once
#include "EnemyObject.h"

class SnailEnemy : public EnemyObject
{
public:
	explicit SnailEnemy(Game* game);
	void Update(float deltaTime) override;
	void OnRespawn() override;

private:
	Animations _unhideAnimation;

	bool _hidden = true;
	bool _canShow = true;
	float _sqrDistance = 250.f * 250.f; // 250 pixels
};

