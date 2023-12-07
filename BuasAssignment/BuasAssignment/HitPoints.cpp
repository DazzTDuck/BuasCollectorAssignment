#include "Hitpoints.h"

HitPoints::HitPoints(int hitPointsAmount)
{
	_hitPoints = hitPointsAmount;
	_maxHitPoints = hitPointsAmount;
}

void HitPoints::RemoveHitPoint()
{
	if(_hitPoints - 1 >= 0) //make sure number does not go below zero
		_hitPoints -= 1;
}

void HitPoints::ResetHitPoints()
{
	_hitPoints = _maxHitPoints;
}

int HitPoints::GetCurrentHitPoints() const
{
	return _hitPoints;
}
