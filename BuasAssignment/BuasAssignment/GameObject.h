#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animations.h"

class Game;

class GameObject
{
public:
	explicit GameObject(Game* game);

	sf::Vector2f objectScale = sf::Vector2f(2.f, 2.f);
	sf::Vector2f objectPosition = sf::Vector2f(500.f, 100.f);
	sf::Vector2f spriteOrigin = sf::Vector2f(0.f, 0.f);
	sf::Vector2f respawnLocation = sf::Vector2f(500.f, 100.f);
	float objectMass = 1.f;
	float maxVelocity = 15.f;

	bool drawCollider = false;
	float colliderDrawThickness = 1.f;

	void SetVelocity(sf::Vector2f velocity);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void AddVelocity(sf::Vector2f velocity);
	void ApplyForce(sf::Vector2f force, float deltaTime, bool onlyColliding = false);
	void ApplyImpulse(sf::Vector2f impulse, float deltaTime);
	void FlipSprite(float originalScaleX);
	sf::FloatRect GetBounds() const;
	sf::Vector2f GetVelocity() const;

	virtual void Update(float deltaTime);
	virtual void Start();
	virtual void Draw(sf::RenderWindow& window);
	virtual void CheckOutOfBounds(sf::RenderWindow& window);

	virtual ~GameObject();

protected:

	Game* _game = nullptr;

	sf::Vector2f _velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _acceleration = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _overlapCollision;
	float _objectDrag = 0.95f;

	bool _grounded = false;
	const float _minSqrCollisionOverlap = 4.f * 4.f; //4 pixels

	sf::RectangleShape _collider;
	sf::Sprite _sprite;
	sf::Vector2f _pointL = {0.f, 0.f};
	sf::Vector2f _pointR = { 0.f, 0.f };

	sf::Texture _defaultTexture;
};

