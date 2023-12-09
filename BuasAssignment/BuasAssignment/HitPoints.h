#pragma once
class HitPoints
{
public:
	explicit HitPoints();

	void RemoveHitPoint();
	void ResetHitPoints();
	void SetHitPoints(int newHitPoints);
	int GetCurrentHitPoints() const;

private:

	int _hitPoints = 0;
	int _maxHitPoints = 0;
};

