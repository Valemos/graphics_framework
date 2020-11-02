#pragma once

#include "../draw_objects/Object3D.h"
#include "../draw_objects/Quad.h"

class Cube : public Object3D
{

public:
	Cube(glm::vec3 surface_color, glm::vec3 edge_color, float edge_length = 1.f) :
		Object3D(surface_color, edge_color, {1, 1, 1})
	{
		figure_scale = { edge_length, edge_length, edge_length };
		
		std::vector<Vector3> cube_vertices;
		cube_vertices.reserve(8);

		Vector3 cur_vertex{ 0, 0, 0 };

		cube_vertices.push_back(cur_vertex);
		cur_vertex.x += 1;
		cube_vertices.push_back(cur_vertex);
		cur_vertex.y += 1;
		cube_vertices.push_back(cur_vertex);
		cur_vertex.x -= 1;
		cube_vertices.push_back(cur_vertex);

		cur_vertex.z += 1;

		cube_vertices.push_back(cur_vertex);
		cur_vertex.x += 1;
		cube_vertices.push_back(cur_vertex);
		cur_vertex.y -= 1;
		cube_vertices.push_back(cur_vertex);
		cur_vertex.x -= 1;
		cube_vertices.push_back(cur_vertex);

		// Load to GL buffer
		InitBuffers(
			cube_vertices,
			{
				new Quad({0, 1, 2, 3}),
				new Quad({4, 5, 6, 7}),
				new Quad({6, 5, 2, 1}),
				new Quad({0, 3, 4, 7}),
				new Quad({7, 6, 1, 0}),
				new Quad({2, 3, 4, 5})
			});
	}
};
