#ifndef GRAVITY_SIMULATION_CONSTANTS
#define GRAVITY_SIMULATION_CONSTANTS

#include "Vector3.h"

class UniverseConstants
{
public:
	UniverseConstants(float gravity_constant = 0.01f, float time_step = 0.01f) {
		UniverseConstants::gravity_constant = gravity_constant;
		UniverseConstants::time_step = time_step;
		coordinate_scale = Vector3{ 1.0, 1.0, 1.0 };
	}

	float gravity_constant;
	float time_step;
	Vector3 coordinate_scale;
};
#endif // !GRAVITY_SIMULATION_CONSTANTS
