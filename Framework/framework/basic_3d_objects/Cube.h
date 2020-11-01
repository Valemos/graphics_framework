#pragma once

#include "../draw_objects/Object3D.h"

class Cube : public Object3D
{

public:
	Cube(float edge_length, glm::vec3 surface_color, glm::vec3 edge_color) :
		Object3D(surface_color, edge_color, {1, 1, 1})
	{
		
	}
};
