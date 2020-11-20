#ifndef GRAVITY_SIMULATION_CONSTANTS
#define GRAVITY_SIMULATION_CONSTANTS

#include "Vector3.h"

class UniverseConstants
{
public:
	UniverseConstants(float gravity_constant = 0.01f, float time_step = 0.01f): border_left(0), border_right(0),
		border_top(0),
		border_bottom(0)
	{
		UniverseConstants::gravity_constant = gravity_constant;
		UniverseConstants::time_step = time_step;
		coordinate_scale = Vector3{1.0, 1.0, 1.0};
	}

	void SetBorders(float left, float right, float top, float bottom)
	{
		border_left = left;
		border_right = right;
		border_top = top;
		border_bottom = bottom;
	}
	
	float border_left;
	float border_right;
	float border_top;
	float border_bottom;
	
	float gravity_constant;
	float time_step;
	Vector3 coordinate_scale;
};
#endif // !GRAVITY_SIMULATION_CONSTANTS
