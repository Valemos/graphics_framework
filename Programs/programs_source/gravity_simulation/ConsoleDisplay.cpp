#include "ConsoleDisplay.h"

#include <clocale>

#include "objects/CelestialBody.h"
#include "UniverseConstants.h"
#include "Simulation.h"

ConsoleDisplay::ConsoleDisplay() {
	SetConsoleOutputCP(65001);
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

// objects must be Displayable subclass
void ConsoleDisplay::ShowGameInformation(std::vector<CelestialBody*> objects, const UniverseConstants& constants, std::string info, bool rewrite) const
{
	if (rewrite)
		SetConsoleCursorPosition(consoleHandle, COORD{ 0, 0 });

	for (CelestialBody* body : objects) {
		body->Display();

		// show accelerations to other objects
		for (CelestialBody* current_object : objects) {
			if (current_object != body) {
				const Vector3 acceleration = Simulation::CalculateAcceleration(objects, body, constants);
				const float dist = sqrt(body->Position().DistanceSquared(current_object->Position()));
				printf("\nAccl to %s\tX: %.3f Y: %.3f", current_object->name.c_str(), acceleration.x, acceleration.y);
				printf("\nDist to %s\t%.3f", current_object->name.c_str(), dist);
			}
		}

		std::cout << std::endl;
	}

	std::cout << info << std::endl;
}
