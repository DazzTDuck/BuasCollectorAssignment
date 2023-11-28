#include "MathFunctions.h"
#include <cmath>
#include <iostream>
#include <string>

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


bool MathFunctions::AreBoundsColliding(sf::FloatRect aRect, sf::FloatRect bRect, sf::Vector2f& penetration)
{
	sf::FloatRect minkowskiDifference;

	minkowskiDifference.top = aRect.top - (bRect.top + bRect.height);
	minkowskiDifference.height = aRect.height + bRect.height;
	minkowskiDifference.left = aRect.left - (bRect.left + bRect.width);
	minkowskiDifference.width = aRect.width + bRect.width;

	if(minkowskiDifference.contains(0, 0))
	{
		float min = FLT_MAX;

		if (abs(minkowskiDifference.left) < min)
		{
			min = abs(minkowskiDifference.left);
			penetration = { minkowskiDifference.left, 0.f };
		}

		if (abs(minkowskiDifference.left + minkowskiDifference.width) < min)
		{
			min = abs(minkowskiDifference.left + minkowskiDifference.width);
			penetration = { minkowskiDifference.left + minkowskiDifference.width , 0.f };
		}

		if (abs(minkowskiDifference.top) < min)
		{
			min = abs(minkowskiDifference.top);
			penetration = { 0.f , minkowskiDifference.top };
		}

		if (abs(minkowskiDifference.top + minkowskiDifference.height) < min)
		{
			min = abs(minkowskiDifference.top + minkowskiDifference.height);
			penetration = { 0.f , minkowskiDifference.top + minkowskiDifference.height };
		}

		return true;
	}

	penetration = { 0.f, 0.f };
	return false;
}

bool MathFunctions::IsPointInBounds(sf::Vector2f point, sf::FloatRect box)
{
	return point.x >= box.left && point.x <= box.left + box.width &&
		point.y >= box.top && point.y <= box.top + box.height;
}

float MathFunctions::Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
