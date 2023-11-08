#pragma once
#include <SFML/Graphics.hpp>

class TileObject
{
public:
	TileObject(sf::Sprite* sprite);

	bool drawCollider = false;
	float colliderDrawThickness = 1.f;

	sf::Sprite* GetSprite() const;

	virtual void Update(float deltaTime);
	virtual void Start();
	virtual void Draw(sf::RenderWindow& window);

	virtual ~TileObject();

private:

	sf::Sprite* _sprite;
	sf::RectangleShape _collider;
};


