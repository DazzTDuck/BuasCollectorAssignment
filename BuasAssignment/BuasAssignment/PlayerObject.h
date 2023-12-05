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
	void Draw(sf::RenderWindow& window) override;

private:
	float _playerSpeed = 310.f;
	float _jumpHeight = 35.f;
	float _jumpTime = 0.05f;
	float _jumpReactivateDelay = .5f;
	float _attackDelay = 0.125f * 4.f; //4 animation frames

	float _currentDelay = 0.f;
	float _actionDelay = 0.f;
	bool _actionActive = false;

	int _coinsCollected = 0;
	bool _attacking = false;
	bool _hasAttacked = false;

	sf::Vector2f _pointHead = { 0.f, 0.f };

	sf::RectangleShape _hitBox;
	sf::Vector2f _hitBoxOffset = { 0.f, 0.f };

	sf::Texture _idleTexture;
	sf::Texture _runTexture;
	sf::Texture _jumpTexture;
	sf::Texture _attackTexture;

	Animations _idleAnimation;
	Animations _runAnimation;
	Animations _jumpAnimation;
	Animations _attackAnimation;
};

