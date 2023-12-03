#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animations.h"

class Game;

class GameObject
{
public:
	GameObject(Game* game);

	std::string objectName = "Coin";
	sf::Vector2f objectScale = sf::Vector2f(2.f, 2.f);
	sf::Vector2f objectPosition;
	sf::Vector2f spriteOrigin = sf::Vector2f(0.f, 0.f);
	sf::Vector2f respawnLocation;
	float objectMass;
	float maxVelocity = 15.f;

	bool drawCollider = false;
	bool isDisabled = false;
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

	void PlaySound(const std::string& soundName, float volume);
	sf::Sound sound;

	virtual ~GameObject();

protected:

	Game* _game = nullptr;

	sf::Vector2f _velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _acceleration = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _overlapCollision;
	float _objectDrag = 0.95f;

	bool _hasGravity = true;
	bool _grounded = false;
	const float _minSqrCollisionOverlap = 2.f * 2.f; //2 pixels

	sf::RectangleShape _collider;
	sf::Sprite _sprite;
	sf::Vector2f _pointL = {0.f, 0.f};
	sf::Vector2f _pointR = { 0.f, 0.f };

	sf::Texture _defaultTexture;
};

