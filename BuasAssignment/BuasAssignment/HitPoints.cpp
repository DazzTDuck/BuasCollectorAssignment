#include "Hitpoints.h"

HitPoints::HitPoints() = default;

void HitPoints::RemoveHitPoint()
{
	if(_hitPoints - 1 >= 0) //make sure number does not go below zero
		_hitPoints -= 1;
}

void HitPoints::ResetHitPoints()
{
	_hitPoints = _maxHitPoints;
}

void HitPoints::SetHitPoints(int newHitPoints)
{
	_hitPoints = newHitPoints;
	_maxHitPoints = newHitPoints;
}

int HitPoints::GetCurrentHitPoints() const
{
	return _hitPoints;
}
