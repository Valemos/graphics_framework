#pragma once

#include "Drawable.h"
#include "Vector3.h"
#include <glm/glm.hpp>

class Object3D : public Drawable
{
public:
	glm::vec3 primary_color{};
	glm::vec3 edge_color{};
	glm::vec3 figure_scale{};

	Object3D(glm::vec3 surface_color, glm::vec3 edge_color, glm::vec3 figure_scale = {1, 1, 1}) :
		primary_color(surface_color), edge_color(edge_color), figure_scale(figure_scale) {}
	
	void LoadGLTransform(Renderer& renderer, const Vector3& position) const override;
	void Draw(Renderer& renderer) override;
	void DrawWireframe(Renderer& renderer) override;
};
