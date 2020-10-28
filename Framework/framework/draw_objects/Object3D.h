#pragma once

#include "Drawable.h"
#include <glm/glm.hpp>"

class Object3D : public Drawable
{
public:
	glm::vec3 surface_color{};
	glm::vec3 edge_color{};
	glm::vec3 figure_scale{};
	
	void Draw(const Renderer& renderer, const Vector3& position) override;
};

