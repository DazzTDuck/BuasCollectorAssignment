#pragma once
#include <SFML/Graphics.hpp>

class Animations
{

public:
	Animations(int amountOfFrames, int widthStep, int height, int top);

	bool PlayAnimation(sf::Sprite& sprite, float deltaTime);
	int GetAnimationStep() const;
	void ResetAnimation();
	bool HasLastFramePlayed() const;

	//static const std::map<std::string, sf::IntRect> animations;

private:

	int _animationStep = 1;
	int _maxAnimationStep;
	float _frameTime = (1.f / 8.f);
	float _frames = 0;
	bool _lastFramePlayed = false;
	int _widthStep;
	int _height;
	int _top;
};