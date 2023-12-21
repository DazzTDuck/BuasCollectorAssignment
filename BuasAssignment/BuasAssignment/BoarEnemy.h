#pragma once
#include "EnemyObject.h"
class BoarEnemy : public EnemyObject
{
public:
	explicit BoarEnemy(Game* game);

	void Update(float deltaTime) override;
	void OnRespawn() override;
};

