#include "TileObject.h"

#include <iostream>

TileObject::TileObject(sf::Sprite* sprite):
	_sprite(),
	_collider()
{
	_sprite = sprite;

	_collider.setSize(_sprite->getGlobalBounds().getSize());
	_collider.setPosition(_sprite->getPosition());
	_collider.setOutlineColor(sf::Color::White);
	_collider.setOutlineThickness(colliderDrawThickness);
	_collider.setFillColor(sf::Color::Transparent);

	startPosition = _sprite->getPosition();
}

void TileObject::Start()
{
}

sf::Sprite* TileObject::GetSprite() const
{
	return _sprite;
}

void TileObject::Update(float deltaTime)
{
}

void TileObject::Draw(sf::RenderWindow& window)
{
	if (drawCollider)
		window.draw(_collider);

	window.draw(*_sprite);
}

TileObject::~TileObject() = default;
