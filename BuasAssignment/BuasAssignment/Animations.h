#pragma once
#include <SFML/Graphics.hpp>

class Animations
{

public:
	Animations(int amountOfFrames);

	bool PlayAnimation(const std::string& animation, sf::Sprite& sprite, float deltaTime);
	int GetAnimationStep() const;

	//static const std::map<std::string, sf::IntRect> animations;

private:

	int _animationStep = 1;
	int _maxAnimationStep;
	float _frameTime = (1.f / 8.f);
	float _frames = 0;
};