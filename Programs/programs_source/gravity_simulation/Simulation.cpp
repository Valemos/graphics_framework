#include "Simulation.h"

#include <iostream>
#include <string>
#include <cstdlib>


void Simulation::AddCelestialBody(CelestialBody* object)
{
	objects_.push_back(object);
}

void Simulation::RemoveCelestialBody(int index)
{
	objects_.erase(objects_.begin() + index);
}

void Simulation::SetOrbit(CelestialBody* target, CelestialBody* satellite, const UniverseConstants& constants)
{
	const float speedModule = sqrt(constants.gravity_constant * (target->Mass() + satellite->Mass())
							/ target->Position().DistanceSquared(satellite->Position()));

	const Vector3 direction = target->Position().Direction(satellite->Position());
	const Vector3 ortVector = Vector3(-direction.y, direction.x);

	satellite->SetSpeed(ortVector * speedModule);
}

void Simulation::ResetSimulation()
{
	objects_.clear();
}

/// 1. updates objects' velocities according to gravity laws
/// 2. updates position for every simulated object
/// returns false if simulation stopped, true otherwise
bool Simulation::SimulateStep(const UniverseConstants& constants)
{
	for (auto body : objects_) {
		body->UpdateSpeed(CalculateAcceleration(objects_, body, constants), constants);
		body->UpdatePosition();
		
		auto* const collided = body->CheckCollision(objects_);
		if (collided != nullptr) {
			Vector3 new_speed = body->Speed();

			const auto distance = body->Position().Distance(collided->Position());
			auto collision_norm = body->Position().Direction(collided->Position(), distance).Normal();

			// use reflection formula to calculate new velocity
			auto speed_norm = body->Speed().Normal();
			auto reflection_norm = speed_norm - 2 * collision_norm.ScalarMultiply(speed_norm) * collision_norm;

			body->Speed() = 0.3 * body->Speed().Length() * reflection_norm;
		}
	}
	return true;
}

Vector3 Simulation::CalculateAcceleration(const std::vector<CelestialBody*>& other_objects, CelestialBody* target, const UniverseConstants& universe)
{
	Vector3 a = Vector3(0, 0);

	for (CelestialBody* object : other_objects) {
		if (object != target) {
			const float dist = object->Position().DistanceSquared(target->Position());
			Vector3 direction = object->Position().Direction(target->Position(), sqrt(dist));
			a += direction * (universe.gravity_constant * object->Mass() / dist);
		}
	}

	return a;
}
