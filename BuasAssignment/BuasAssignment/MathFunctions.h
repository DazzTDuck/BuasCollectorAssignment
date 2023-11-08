#pragma once
#include <SFML/System/Vector2.hpp>

namespace MathFunctions
{
	extern sf::Vector2f Normalize(sf::Vector2f);
	extern float Magnitude(sf::Vector2f);
	extern float SqrMagnitude(sf::Vector2f);
	extern float GetSqrDistance(sf::Vector2f a, sf::Vector2f b);
	extern float Clamp01(float value);
}

