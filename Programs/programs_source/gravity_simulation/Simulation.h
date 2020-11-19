#ifndef GRAVITY_SIMULATION
#define GRAVITY_SIMULATION

#include <mutex>
#include <vector>
#include "Vector3.h"
#include "UniverseConstants.h"
#include "objects/CelestialBody.h"
#include "ConsoleDisplay.h"
#include "Program.h"

class Renderer;
class ConsoleDisplay;
class CelestialBody;
class UniverseConstants;

class Simulation
{
	std::vector<CelestialBody*> objects_;

public:

	Simulation() = default;
	
	//Manage simulated objects
	void AddCelestialBody(CelestialBody* gObject);
	void RemoveCelestialBody(int index);

	void SetOrbit(CelestialBody* target, CelestialBody* satellite, const UniverseConstants& constants);

	void ResetSimulation();
	bool SimulateStep(const UniverseConstants& constants);

	/// for container of CelestialBody's object pointers 
	/// calculates acceleration due to gravity
	static Vector3 CalculateAcceleration(const std::vector<CelestialBody*>& other_objects, CelestialBody* target, const UniverseConstants& universe);

	const std::vector<CelestialBody*>& Objects() const {
		return objects_;
	}
};

#endif