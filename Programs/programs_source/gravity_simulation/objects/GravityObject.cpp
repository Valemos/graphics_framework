#include "GravityObject.h"
#include "../UniverseConstants.h"

GravityObject::GravityObject(float radius, float surfaceGravity, float mass, const UniverseConstants& constants)
{
	if (surfaceGravity != 0.f)
	{
		mass_ = surfaceGravity * radius * radius / constants.gravity_constant;
	}
	else
	{
		mass_ = mass;
	}

	radius_ = radius;
	speed_ = Vector3(0, 0);
	position_ = Vector3(0, 0);
}

void GravityObject::UpdateSpeed(Vector3 acceleration, const UniverseConstants& constants)
{
	this->speed_ += acceleration * constants.time_step;
}


/// updates object position according to current speed
void GravityObject::UpdatePosition()
{
	position_ += speed_;
}

void GravityObject::RevertPosition()
{
	position_ -= speed_;
}
