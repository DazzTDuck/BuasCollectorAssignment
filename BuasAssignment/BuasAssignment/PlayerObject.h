#pragma once
#include "GameObject.h";

class PlayerObject : public GameObject
{

public:
	PlayerObject();


	void Update(float deltaTime) override;
	void Start() override;

private:

	float _playerSpeed = 310.f;
	float _jumpHeight = 10.f;
	float _jumpTime = 0.05f;

	sf::Texture _idleTexture;
	sf::Texture _runTexture;
	sf::Texture _jumpTexture;

	Animations _idleAnimation;
	Animations _runAnimation;
	Animations _jumpAnimation;
};

