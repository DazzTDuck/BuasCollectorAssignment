#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace MathFunctions
{
	extern sf::Vector2f Normalize(sf::Vector2f);
	extern float Magnitude(sf::Vector2f);
	extern float SqrMagnitude(sf::Vector2f);
	extern float GetSqrDistance(sf::Vector2f a, sf::Vector2f b);
	extern float Clamp01(float value);

	bool AreBoundsColliding(sf::FloatRect aRect, sf::FloatRect bRect, sf::Vector2f& penetration);
	bool IsPointInBounds(sf::Vector2f point, sf::FloatRect box);
}

