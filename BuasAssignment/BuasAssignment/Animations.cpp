#include "Animations.h"

Animations::Animations(int amountOfFrames, int widthStep, int height, int top) :
	_maxAnimationStep()
{
	_maxAnimationStep = amountOfFrames;
	_widthStep = widthStep;
	_height = height;
	_top = top;
}

bool Animations::PlayAnimation(sf::Sprite& sprite, float deltaTime)
{
	_frames += deltaTime;

	if (_frames > _frameTime)
	{
		_lastFramePlayed = false;
		//sprite.setTextureRect(animations.at(animation + "_" + std::to_string(_animationStep)));
		//sprite.setTextureRect({ 96 * (_animationStep - 1), 0, 96, 80});
		sprite.setTextureRect({ _widthStep * (_animationStep - 1), _top, _widthStep, _height });

		_animationStep++;

		if (_animationStep > _maxAnimationStep)
		{
			_lastFramePlayed = true;
			_animationStep = 1;
		}

		_frames = 0;

		return true;
	}

	return false;	
}

int Animations::GetAnimationStep() const
{
	return _animationStep;
}

void Animations::ResetAnimation()
{
	_animationStep = 1;
	_lastFramePlayed = false;
}

bool Animations::HasLastFramePlayed() const
{
	return _lastFramePlayed;
}

//const std::map<std::string, sf::IntRect> Animations::animations =
//{
//	// left pixel, top pixel, pixel width, pixel height
//
//	//idle animation frames
//	{"PlayerIdle_1", {0, 0, 96, 80}},
//	{"PlayerIdle_2", {96, 0, 96, 80}},
//	{"PlayerIdle_3", {192, 0, 96, 80}},
//	{"PlayerIdle_4", {288, 0, 96, 80}},
//	
//	//run animation frames
//	{"PlayerRun_1", {28, 16, 35, 52}},
//	{"PlayerRun_2", {106, 16, 35, 52}},
//	{"PlayerRun_3", {190, 16, 35, 52}},
//	{"PlayerRun_4", {272, 16, 35, 52}},
//	{"PlayerRun_5", {348, 16, 35, 52}},
//	{"PlayerRun_6", {428, 16, 35, 52}},
//	{"PlayerRun_7", {512, 16, 35, 52}},
//	{"PlayerRun_8", {591, 16, 35, 52}},
//
//	//jump in air animation frames
//	{"PlayerJumpAir_1", {261, 3, 33, 61}},
//	{"PlayerJumpAir_2", {327, 3, 33, 61}},
//
//	//frames first attack
//	{"PlayerFirstAttack_1", {0, 0, 96, 80}},
//	{"PlayerFirstAttack_2", {96, 0, 96, 80}},
//	{"PlayerFirstAttack_3", {192, 0, 96, 80}},
//	{"PlayerFirstAttack_4", {288, 0, 96, 80}},
//
//	//second part of attack
//	{"PlayerSecondAttack_1", {416, 16, 34, 48}},
//	{"PlayerSecondAttack_2", {327, 3, 33, 61}},
//	{"PlayerSecondAttack_3", {327, 3, 33, 61}},
//	{"PlayerSecondAttack_4", {327, 3, 33, 61}}
//};