#ifndef GRAVITY_SIMULATION_DISPLAY
#define GRAVITY_SIMULATION_DISPLAY

class CelestialBody;
class UniverseConstants;

#include <Windows.h>
#include <iostream>
#include <vector>

class ConsoleDisplay
{
public:
	ConsoleDisplay();
	~ConsoleDisplay() {};

	void ShowGameInformation(std::vector<CelestialBody*> objects, const UniverseConstants& constants, std::string info, bool rewrite) const;

private:
	HANDLE consoleHandle;
};

#endif // !DISPLAY
