#ifndef GRAVITY_SIMULATION
#define GRAVITY_SIMULATION

class Renderer;

#include <Windows.h>
#include <iostream>
#include <vector>
#include "Vector3.h"
#include "UniverseConstants.h"
#include "objects/CelestialBody.h"


class Simulation
{
	
	std::vector<CelestialBody*> objects_;
	HANDLE console_handle_;

public:

	Simulation();
	~Simulation();
	
	//Manage simulated objects
	void AddCelestialBody(CelestialBody* gObject);
	void RemoveCelestialBody(int index);

	void SetOrbit(CelestialBody* target, CelestialBody* satellite, const UniverseConstants& constants);

	void ResetSimulation();
	bool SimulateStep(const UniverseConstants& constants);
	void ShowInformation(const UniverseConstants& constants, std::string info, bool rewrite);

	/// for container of CelestialBody's object pointers 
	/// calculates acceleration due to gravity
	static Vector3 CalculateAcceleration(const std::vector<CelestialBody*>& other_objects, CelestialBody* target, const UniverseConstants& universe);

	const std::vector<CelestialBody*>& Objects() const {
		return objects_;
	}
};

#endif