#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animations.h"

class Game;

class GameObject
{
public:
	GameObject();

	sf::Vector2f objectScale = sf::Vector2f(2.f, 2.f);
	sf::Vector2f objectPosition = sf::Vector2f(150.f, 100.f);
	sf::Vector2f spriteOrigin = sf::Vector2f(0.f, 0.f);
	float objectMass = 1.f;
	float maxVelocity = 15.f;

	bool drawCollider = false;
	float colliderDrawThickness = 1.f;

	void SetVelocity(sf::Vector2f velocity);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void AddVelocity(sf::Vector2f velocity);
	void ApplyForce(sf::Vector2f force, float deltaTime, bool onlyColliding = false);
	void CheckOutOfBounds(sf::RenderWindow& window);
	sf::Vector2f GetVelocity() const;

	virtual void Update(float deltaTime);
	virtual void Start();
	virtual void Draw(sf::RenderWindow& window);

	Game* game = nullptr;

	virtual ~GameObject();

private:

	void FlipSprite(float originalScaleX);

	sf::Vector2f _velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _acceleration = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _overlapCollision;

	bool _grounded = false;
	const float _minSqrCollisionOverlap = 4.f * 4.f; //4 pixels

	sf::Sprite _sprite;
	sf::RectangleShape _collider;
	sf::Vector2f _pointL = {0.f, 0.f};
	sf::Vector2f _pointR = { 0.f, 0.f };

	sf::Texture _idleTexture;
	sf::Texture _runTexture;
	sf::Texture _jumpTexture;

	Animations _idleAnimation;
	Animations _runAnimation;
	Animations _jumpAnimation;
};

