#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>

#include "Hitpoints.h"

enum ObjectType
{
	GAMEOBJECT,
	ENEMY,
	PLAYER
};

class Game;

class GameObject
{
public:
	explicit GameObject(Game* game);

	std::string objectName = "Object";
	sf::Vector2f objectScale = sf::Vector2f(2.f, 2.f);
	sf::Vector2f objectPosition;
	sf::Vector2f spriteOrigin = sf::Vector2f(0.f, 0.f);
	sf::Vector2f respawnLocation;
	ObjectType objectType = GAMEOBJECT;
	float objectMass;

	bool drawCollider = false;
	bool isDisabled = false;
	float colliderDrawThickness = 1.f;

	void SetVelocity(sf::Vector2f velocity);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void AddVelocity(sf::Vector2f velocity);
	void ApplyForce(sf::Vector2f force, float deltaTime);
	void ApplyImpulse(sf::Vector2f impulse, float deltaTime);
	void FlipSprite(float originalScaleX, float widthMultiplier, bool flipped = false);
	sf::FloatRect GetBounds() const;
	sf::Vector2f GetVelocity() const;
	sf::Sprite& GetSprite();

	virtual void Update(float deltaTime);
	virtual void Start();
	virtual void Draw(sf::RenderWindow& window);
	virtual void CheckOutOfBounds(sf::RenderWindow& window);
	virtual void OnRespawn();

	void PlaySound(const std::string& soundName, float volume);
	sf::Sound sound;

	HitPoints hitPoints;

	virtual ~GameObject();

protected:

	Game* _game = nullptr;

	sf::Vector2f _velocity = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _acceleration = sf::Vector2f(0.f, 0.f);
	sf::Vector2f _overlapCollision;
	sf::Vector2f _originalOrigin = sf::Vector2f(0.f, 0.f);
	float _objectDrag = 0.9f;
	float _maxVelocity = 15.f;

	int _objectHitPoints = 1;

	bool _hasGravity = true;
	bool _isFlipped = false;
	bool _grounded = false;
	bool _leftPointGrounded = false;
	bool _rightPointGrounded = false;

	const float _minSqrCollisionOverlap = 1.f * 1.f; //1 pixels

	sf::RectangleShape _collider;
	sf::Sprite _sprite;
	sf::Vector2f _pointL;
	sf::Vector2f _pointR;

	sf::Texture _defaultTexture;
};

