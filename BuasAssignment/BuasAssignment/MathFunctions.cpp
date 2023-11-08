#include "MathFunctions.h"
#include <cmath>

sf::Vector2f MathFunctions::Normalize(sf::Vector2f vector2)
{
	float const mag = Magnitude(vector2);

	if (mag == 0.0f)
		return { 0.0f, 0.0f};

	return vector2 / mag;
}

float MathFunctions::SqrMagnitude(sf::Vector2f vector2)
{
	return vector2.x * vector2.x + vector2.y * vector2.y;
}


float MathFunctions::Magnitude(sf::Vector2f vector2)
{
	return sqrt(SqrMagnitude(vector2));
}

float MathFunctions::GetSqrDistance(sf::Vector2f a, sf::Vector2f b)
{
	return SqrMagnitude(b - a);
}

float MathFunctions::Clamp01(float value)
{
	if (value < 0.f) return 0.f;
	if (value > 1.f) return 1.f;
	return value;
}

