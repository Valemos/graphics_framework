#ifndef GRAVITY_SIMULATION_CELESTIAL_BODY
#define GRAVITY_SIMULATION_CELESTIAL_BODY
#include "draw_objects/Drawable.h"

class UniverseConstants;
class Renderer;

#include <iostream>
#include <vector>

#include "GravityObject.h"
#include "Displayable.h"
#include "draw_objects/Figure2D.h"


class CelestialBody : public GravityObject, public Displayable
{
	static const int s_circle_points = 20;
	UniverseConstants* constants_ = nullptr;
	Figure2D* circle_;

public:
	std::string name; 
	
	CelestialBody(std::string name, Vector3 color, UniverseConstants* constants, float radius, float surfaceGravity = 0.f, float mass = 0.f);

	CelestialBody* CheckCollision(const std::vector<CelestialBody*>& bodies);

	void InitCirclePoints();
	void Draw(Renderer& renderer) const;
	
	void Display() override;
};


#endif // !GRAVITY_SIMULATION_CELESTIAL_BODY
