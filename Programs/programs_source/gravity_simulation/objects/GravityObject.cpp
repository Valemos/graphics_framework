#include "GravityObject.h"
#include "../UniverseConstants.h"

constexpr float pi = 3.1415926535f;


GravityObject::GravityObject(): mass_(1), radius_(1)
{	
	speed_ = Vector3(0, 0);
	position_ = Vector3(0, 0);
}

float GravityObject::MassGravityEquation(float surface_gravity, float radius, float gravity_constant)
{
	return surface_gravity * radius * radius / gravity_constant;
}

float GravityObject::MassDensityEquation(float density, float radius)
{
	return density * 4.f / 3 * pi * radius * radius * radius;
}

float GravityObject::GravityEquation(float mass, float radius, float gravity_constant)
{
	return mass * gravity_constant / (radius * radius);
}

float GravityObject::DensityMassEquation(float mass, float radius)
{
	// volume divided by mass
	// we suppose, that objects is perfect spheres
	return mass * 3 / (4 * pi * radius * radius * radius);
}

float GravityObject::RadiusEquation(float mass, float density)
{
	return (float) pow((3 * density * mass) / (4 * pi), 1 / 3.0);
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

void GravityObject::SetMass(float mass)
{
	mass_ = mass;
}

void GravityObject::SetDensity(float density, const UniverseConstants& constants)
{
	// conserve radius and change mass
	mass_ = MassDensityEquation(density, radius_);
}

void GravityObject::SetRadius(float radius)
{
	radius_ = radius;
}

void GravityObject::SetSurfaceGravity(float gravity, const UniverseConstants& constants)
{
	// change mass and density of an object
	mass_ = MassGravityEquation(gravity, radius_, constants.gravity_constant);
}

float GravityObject::GetSurfaceGravity(const UniverseConstants& constants) const
{
	return GravityEquation(mass_, radius_, constants.gravity_constant);
}
