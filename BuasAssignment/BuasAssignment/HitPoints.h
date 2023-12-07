#pragma once
class HitPoints
{
public:
	explicit HitPoints(int hitPointsAmount);

	void RemoveHitPoint();
	void ResetHitPoints();
	int GetCurrentHitPoints() const;

private:

	int _hitPoints;
	int _maxHitPoints;
};

