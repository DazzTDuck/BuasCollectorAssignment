#pragma once
#include "GameObject.h";

class PlayerObject : public GameObject
{

public:
	explicit PlayerObject(Game* game);

	void CheckOutOfBounds(sf::RenderWindow& window) override;
	void GameObjectColliding();
	void Update(float deltaTime) override;
	void Start() override;

private:

	float _playerSpeed = 310.f;
	float _jumpHeight = 35.f;
	float _jumpTime = 0.05f;
	float _jumpReactivateDelay = 1.5f;
	float _jumpDelay = 0.f;
	int _coinsCollected = 0;
	bool _jumped = false;

	sf::Texture _idleTexture;
	sf::Texture _runTexture;
	sf::Texture _jumpTexture;

	Animations _idleAnimation;
	Animations _runAnimation;
	Animations _jumpAnimation;
};

