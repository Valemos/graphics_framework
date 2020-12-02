#pragma once

#include "../framework/draw_objects/Object3D.h"
#include "draw_objects/primitives/Triangle.h"
#include "cmath"

class Sphere : public Object3D
{
	const unsigned detalisation_level = 2;
	
public:
	Sphere(const glm::vec3& surface_color, const glm::vec3& edge_color, const glm::vec3& figure_scale = {1, 1, 1})
		: Object3D(surface_color, edge_color, figure_scale)
	{
		// we create cube with subdivided faces
		std::vector<Vector3> vertices = {
			{-0.26286500f, 0.0000000f, 0.42532500f},
			{0.26286500f, 0.0000000f, 0.42532500f},
			{-0.26286500f, 0.0000000f, -0.42532500f},
			{0.26286500f, 0.0000000f, -0.42532500f},
			{0.0000000f, 0.42532500f, 0.26286500f},
			{0.0000000f, 0.42532500f, -0.26286500f},
			{0.0000000f, -0.42532500f, 0.26286500f},
			{0.0000000f, -0.42532500f, -0.26286500f},
			{0.42532500f, 0.26286500f, 0.0000000f},
			{-0.42532500f, 0.26286500f, 0.0000000f},
			{0.42532500f, -0.26286500f, 0.0000000f},
			{-0.42532500f, -0.26286500f, 0.0000000f}
		};

		for (auto& vertex : vertices)
		{
			vertex.Normalize();
		}

		std::vector<Primitive*>* prev_triangles = new std::vector<Primitive*>
		{
			new Triangle({0, 6,  1}),
			new Triangle({0, 11, 6}),
			new Triangle({1, 4,  0}),
			new Triangle({1, 8,  4}),
			new Triangle({1, 10, 8}),
			new Triangle({2, 5,  3}),
			new Triangle({2, 9,  5}),
			new Triangle({2, 11, 9}),
			new Triangle({3, 7,  2}),
			new Triangle({3, 10, 7}),
			new Triangle({4, 8,  5}),
			new Triangle({4, 9,  0}),
			new Triangle({5, 8,  3}),
			new Triangle({5, 9,  4}),
			new Triangle({6, 10, 1}),
			new Triangle({6, 11, 7}),
			new Triangle({7, 10, 6}),
			new Triangle({7, 11, 2}),
			new Triangle({8, 10, 3}),
			new Triangle({9, 11, 0})
		};
		
		if (detalisation_level > 0)
		{
			// subdivide each triangle into three others
			for (int i = 0; i < detalisation_level; ++i)
			{
				std::vector<Primitive*> * new_triangles = new std::vector<Primitive*>();
				new_triangles->reserve(prev_triangles->size() * 3);
				vertices.reserve(vertices.size() * 2);
				for (auto* triangle : *prev_triangles)
				{
					auto iv0 = triangle->get_indices()[0],
						 iv1 = triangle->get_indices()[1],
						 iv2 = triangle->get_indices()[2];
					auto v0 = vertices[iv0];
					auto v1 = vertices[iv1];
					auto v2 = vertices[iv2];
					auto v3 = ((v0 + v1) * 0.5).Normal();
					auto v4 = ((v1 + v2) * 0.5).Normal();
					auto v5 = ((v2 + v0) * 0.5).Normal();

					// add vertices
					unsigned mid0 = vertices.size();
					vertices.push_back(v3);
					unsigned mid1 = mid0 + 1;
					vertices.push_back(v4);
					unsigned mid2 = mid0 + 2;
					vertices.push_back(v5);

					// add triangles
					new_triangles->push_back(new Triangle({ iv0, mid0, mid2 }));
					new_triangles->push_back(new Triangle({ iv1, mid1, mid0 }));
					new_triangles->push_back(new Triangle({ iv2, mid2, mid1 }));
					new_triangles->push_back(new Triangle({ mid0, mid1, mid2 }));
				}

				for (auto* triangle : *prev_triangles)
				{
					delete triangle;
				}
				delete prev_triangles;
				prev_triangles = new_triangles;
			}
		}
        InitPrimitiveBuffers(vertices, *prev_triangles);
	}
};
