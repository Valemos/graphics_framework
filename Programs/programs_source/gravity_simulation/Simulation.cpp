#include "Simulation.h"

#include <iostream>
#include <string>
#include <cstdlib>


Simulation::Simulation()
{
	SetConsoleOutputCP(65001);
	console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

Simulation::~Simulation()
{
	for(auto* obj : objects_)
	{
		delete obj;
	}
}

void Simulation::AddCelestialBody(CelestialBody* object)
{
	objects_.emplace_back(object);
}

void Simulation::RemoveCelestialBody(int index)
{
	objects_.erase(objects_.begin() + index);
}

void Simulation::SetOrbit(CelestialBody* target, CelestialBody* satellite, const UniverseConstants& constants)
{
	const float speedModule = sqrt(constants.gravity_constant * (target->GetMass() + satellite->GetMass())
							/ target->GetPosition().DistanceSquared(satellite->GetPosition()));

	const Vector3 direction = target->GetPosition().Direction(satellite->GetPosition());
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
	for (auto body_it = objects_.begin(); body_it != objects_.end();) {
		(*body_it)->UpdateSpeed(CalculateAcceleration(objects_, *body_it, constants), constants);
		(*body_it)->UpdatePosition();

		// if body outside border, remove it
		if ((*body_it)->GetPosition().x > constants.border_left &&
			(*body_it)->GetPosition().x < constants.border_right &&
			(*body_it)->GetPosition().x < constants.border_top &&
			(*body_it)->GetPosition().x > constants.border_bottom)
		{
			objects_.erase(body_it);
		}
		else
		{
			++body_it;
		}
		
		//auto* const collided = body->CheckCollision(objects_);
		//if (collided != nullptr) {
		//	Vector3 new_speed = body->Speed();

		//	const auto distance = body->GetPosition().Distance(collided->GetPosition());
		//	auto collision_norm = body->GetPosition().Direction(collided->GetPosition(), distance).Normal();

		//	// use reflection formula to calculate new velocity
		//	auto speed_norm = body->Speed().Normal();
		//	auto reflection_norm = speed_norm - 2 * collision_norm.Dot(speed_norm) * collision_norm;

		//	body->Speed() = 0.3 * body->Speed().Length() * reflection_norm;
		//}
	}
	return true;
}

void Simulation::ShowInformation(const UniverseConstants& constants, std::string info, bool rewrite)
{
	if (rewrite)
		SetConsoleCursorPosition(console_handle_, COORD{ 0, 0 });

	for (CelestialBody* body : objects_) {
		body->Display();

		// show accelerations to other objects
		for (CelestialBody* current_object : objects_) {
			if (current_object != body) {
				const Vector3 acceleration = Simulation::CalculateAcceleration(objects_, body, constants);
				const float dist = sqrt(body->GetPosition().DistanceSquared(current_object->GetPosition()));
				printf("\nAccl to %s\tX: %.3f Y: %.3f", current_object->name.c_str(), acceleration.x, acceleration.y);
				printf("\nDist to %s\t%.3f", current_object->name.c_str(), dist);
			}
		}

		std::cout << std::endl;
	}

	std::cout << info << std::endl;
}

Vector3 Simulation::CalculateAcceleration(const std::vector<CelestialBody*>& other_objects, CelestialBody* target, const UniverseConstants& universe)
{
	Vector3 a = Vector3(0, 0);

	for (CelestialBody* object : other_objects) {
		if (object != target) {
			const float dist = object->GetPosition().DistanceSquared(target->GetPosition());
			Vector3 direction = object->GetPosition().Direction(target->GetPosition(), sqrt(dist));
			a += direction * (universe.gravity_constant * object->GetMass() / dist);
		}
	}

	return a;
}
