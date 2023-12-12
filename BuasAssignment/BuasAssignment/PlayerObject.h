#pragma once
#include "Animations.h"
#include "GameObject.h"

class PlayerObject : public GameObject
{

public:
	explicit PlayerObject(Game* game);

	void CheckOutOfBounds(sf::RenderWindow& window) override;
	void GameObjectColliding(float deltaTime);
	void Update(float deltaTime) override;
	void Start() override;
	void Draw(sf::RenderWindow& window) override;
	void OnRespawn() override;
	void CoinAdded();

private:
	float _playerSpeed = 300.f;
	float _maxMoveVelocity = 10.f;
	float _jumpHeight = 25.f;
	float _jumpTime = 0.05f;
	float _jumpReactivateDelay = .5f;
	float _attackDelay = 0.125f * 4.f; //4 animation frames
	float _playerGetDamageKnockBack = 3500.f;

	float _currentDelay = 0.f;
	float _actionDelay = 0.f;
	bool _actionActive = false;

	int _coinsCollected = 0;
	int _maxCoins = 0;

	bool _attacking = false;
	bool _hasAttacked = false;
	bool _isDead = false;
	float _deathDelay = 0.125f * 9.f; //9 animation frames
	float _hitDelay = 1.0f;

	sf::Vector2f _pointHead = { 0.f, 0.f };

	sf::RectangleShape _hitBox;
	sf::Vector2f _hitBoxOffset = { 0.f, 0.f };

	sf::Texture _idleTexture;
	sf::Texture _runTexture;
	sf::Texture _jumpTexture;
	sf::Texture _attackTexture;
	sf::Texture _deathTexture;

	Animations _idleAnimation;
	Animations _runAnimation;
	Animations _jumpAnimation;
	Animations _attackAnimation;
	Animations _deathAnimation;
};

