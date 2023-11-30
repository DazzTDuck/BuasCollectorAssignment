#include "BackgroundSprite.h"
BackgroundSprite::BackgroundSprite(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture, sf::IntRect rect, float newDepth):
	_sprite()
{
	_sprite = new sf::Sprite;

	_sprite->setPosition(position);
	_sprite->setScale(scale);
	_sprite->setTexture(texture);
	_sprite->setTextureRect(rect);

	_startPosition = position;

	depth = newDepth;
}

void BackgroundSprite::SetPosition(sf::Vector2f newPosition) const
{
	_sprite->setPosition(newPosition);
}

sf::Vector2f BackgroundSprite::GetStartPosition() const
{
	return _startPosition;
}

sf::Sprite* BackgroundSprite::GetSprite() const
{
	return _sprite;
}
