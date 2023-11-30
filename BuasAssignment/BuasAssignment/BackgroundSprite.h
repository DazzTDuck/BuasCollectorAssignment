#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class BackgroundSprite
{
public:
	BackgroundSprite(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture, sf::IntRect rect, float newDepth);
	void SetPosition(sf::Vector2f newPosition) const;
	sf::Vector2f GetStartPosition() const;
	sf::Sprite* GetSprite() const;

	float depth = 0.5f;

private:

	sf::Sprite* _sprite;
	sf::Vector2f _startPosition; 
};

