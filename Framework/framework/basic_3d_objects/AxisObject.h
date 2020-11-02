#pragma once

#include <GL/glew.h>

#include "../draw_objects/Object3D.h"
#include "../draw_objects/Line.h"
#include "glm/gtc/type_ptr.hpp"
#include "../Renderer.h"


class AxisObject : public Object3D
{
public:
	AxisObject(Vector3 main_vector, Vector3 orthogonal, const glm::vec3& surface_color, const glm::vec3& edge_color = {0, 0, 0}, const glm::vec3& figure_scale = { 1, 1, 1 })
		: Object3D(surface_color, edge_color, figure_scale)
	{
		auto face_shift = main_vector.Length() / 16;
		auto cross_product = main_vector.Cross(orthogonal);

		std::vector<Vector3> vertices;
		vertices.reserve(8);
			
		// lower side
		vertices.emplace_back(orthogonal * face_shift);
		vertices.emplace_back(cross_product * face_shift);
		vertices.emplace_back(orthogonal * (-face_shift));
		vertices.emplace_back(cross_product * (-face_shift));

		vertices.emplace_back(vertices[0] + main_vector);
		vertices.emplace_back(vertices[1] + main_vector);
		vertices.emplace_back(vertices[2] + main_vector);
		vertices.emplace_back(vertices[3] + main_vector);

		std::vector<Primitive*> primitives =
		{
			new Quad({0, 1, 2, 3}),
			new Quad({4, 5, 6, 7}),
			new Quad({0, 1, 5, 4}),
			new Quad({1, 2, 6, 5}),
			new Quad({2, 3, 7, 6}),
			new Quad({3, 0, 4, 7})
		};

		InitBuffers(vertices, primitives);
	}
};

class ThreeAxis : public Object3D
{
	AxisObject x_axis_, y_axis_, z_axis_;
	
public:
	ThreeAxis() : Object3D({0, 0, 0}, {0, 0, 0}),
	              x_axis_(AxisObject({1, 0, 0}, {0, 1, 0}, {1, 0, 0})),
	              y_axis_(AxisObject({0, 1, 0}, {0, 0, 1}, {0, 1, 0})),
	              z_axis_(AxisObject({0, 0, 1}, {1, 0, 0}, {0, 0, 1}))
	{
	}

	void SetPosition(const Vector3& position)
	{
		x_axis_.Position() = position;
		y_axis_.Position() = position;
		z_axis_.Position() = position;
	}
	
	void Draw(Renderer& renderer) override
	{
		x_axis_.Draw(renderer);
		y_axis_.Draw(renderer);
		z_axis_.Draw(renderer);
	}

	void DrawWireframe(Renderer& renderer) override
	{
		x_axis_.DrawWireframe(renderer);
		y_axis_.DrawWireframe(renderer);
		z_axis_.DrawWireframe(renderer);
	}
};
