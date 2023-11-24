#include "Animations.h"

Animations::Animations(int amountOfFrames) :
	_maxAnimationStep()
{
	_maxAnimationStep = amountOfFrames;
}

bool Animations::PlayAnimation(const std::string& animation, sf::Sprite& sprite, float deltaTime)
{
	_frames += deltaTime;

	if (_frames > _frameTime)
	{
		sprite.setTextureRect(animations.at(animation + "_" + std::to_string(_animationStep)));
		_animationStep++;

		if (_animationStep > _maxAnimationStep)
			_animationStep = 1;

		_frames = 0;

		return true;
	}

	return false;	
}

const std::map<std::string, sf::IntRect> Animations::animations =
{
	//idle animation frames
	{"PlayerIdle_1", {22, 15, 35, 49}},
	{"PlayerIdle_2", {85, 15, 35, 49}},
	{"PlayerIdle_3", {149, 15, 35, 49}},
	{"PlayerIdle_4", {214, 15, 35, 49}},
	
	//run animation frames
	{"PlayerRun_1", {28, 16, 35, 52}},
	{"PlayerRun_2", {106, 16, 35, 52}},
	{"PlayerRun_3", {190, 16, 35, 52}},
	{"PlayerRun_4", {272, 16, 35, 52}},
	{"PlayerRun_5", {348, 16, 35, 52}},
	{"PlayerRun_6", {428, 16, 35, 52}},
	{"PlayerRun_7", {512, 16, 35, 52}},
	{"PlayerRun_8", {591, 16, 35, 52}},

	//jump in air animation frames
	{"PlayerJumpAir_1", {261, 3, 33, 61}},
	{"PlayerJumpAir_2", {327, 3, 33, 61}}
};