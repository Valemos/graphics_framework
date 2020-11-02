#pragma once

#include "../draw_objects/Object3D.h"
#include "../draw_objects/Triangle.h"
#include "../draw_objects/Quad.h"
#include <math.h>

class Dodecahedron : public Object3D
{
	const float golden_ratio_ = (1 + sqrt(5)) / 2;

	std::vector<Primitive*> CreateRoofPrimitives(const std::vector<unsigned>& cube_face, const std::vector<unsigned>& points, int face_rotation, bool flip_points)
	{
		std::vector<Primitive*> output;
		output.reserve(4);

		output.emplace_back(new Triangle({cube_face[0], cube_face[1], points[0] }));
		output.emplace_back(new Quad({cube_face[1], cube_face[2], points[1], points[0] }));
		output.emplace_back(new Triangle({cube_face[2], cube_face[3], points[1] }));
		output.emplace_back(new Quad({cube_face[3], cube_face[0], points[0], points[1] }));
		
		return output;
	}

public:
	Dodecahedron(const glm::vec3& surface_color, const glm::vec3& edge_color)
		: Object3D(surface_color, edge_color)
	{
		// we construct dodecahedron by Euclid's method from this StackExchange page
		// https://math.stackexchange.com/questions/632936/cleverest-construction-of-a-dodecahedron-icosahedron

		// starting with the cube we use roof like shape and place it on each side of a cube

		std::vector<Vector3> vertices;
		vertices.reserve(8);

		Vector3 cur_vertex{ -1, -1, -1 };

		vertices.push_back(cur_vertex); // 0
		cur_vertex.x += 2;
		vertices.push_back(cur_vertex); // 1
		cur_vertex.y += 2;
		vertices.push_back(cur_vertex); // 2
		cur_vertex.x -= 2;
		vertices.push_back(cur_vertex); // 3

		cur_vertex.z += 2;

		vertices.push_back(cur_vertex); // 4
		cur_vertex.x += 2;
		vertices.push_back(cur_vertex); // 5
		cur_vertex.y -= 2;
		vertices.push_back(cur_vertex); // 6
		cur_vertex.x -= 2;
		vertices.push_back(cur_vertex); // 7

		unsigned index = 8;
		
		// B than C
		std::vector<unsigned> top = { index++, index++ };
		vertices.emplace_back(Vector3{ -1 / golden_ratio_, (1 + 1 / golden_ratio_), 0 });
		vertices.emplace_back(Vector3{ 1 / golden_ratio_, (1 + 1 / golden_ratio_), 0 });

		std::vector<unsigned> bottom = { index++, index++ };
		vertices.emplace_back(Vector3{ -1 / golden_ratio_, -(1 + 1 / golden_ratio_), 0 });
		vertices.emplace_back(Vector3{ 1 / golden_ratio_, -(1 + 1 / golden_ratio_), 0 });

		// front than back vertex
		std::vector<unsigned> right = { index++, index++ };
		vertices.emplace_back(Vector3{ (-1 - 1 / golden_ratio_), 0,  1 / golden_ratio_ });
		vertices.emplace_back(Vector3{ (-1 - 1 / golden_ratio_), 0, -1 / golden_ratio_ });
		
		std::vector<unsigned> left = { index++, index++ };
		vertices.emplace_back(Vector3{-(-1 - 1 / golden_ratio_), 0,  1 / golden_ratio_});
		vertices.emplace_back(Vector3{-(-1 - 1 / golden_ratio_), 0, -1 / golden_ratio_});

		// top than bottom vertex
		std::vector<unsigned> front = { index++, index++ };
		vertices.emplace_back(Vector3{ 0, 1 / golden_ratio_, -(1 + 1 / golden_ratio_) });
		vertices.emplace_back(Vector3{ 0, 1 / golden_ratio_, -(1 + 1 / golden_ratio_) });

		std::vector<unsigned> back = { index++, index++ };
		vertices.emplace_back(Vector3{0, 1 / golden_ratio_, (1 + 1 / golden_ratio_)});
		vertices.emplace_back(Vector3{0, 1 / golden_ratio_, (1 + 1 / golden_ratio_)});


		// Cube faces
		// as seen from -z axis
		std::vector<unsigned> cube_front = { 0, 1, 2, 3 };
		std::vector<unsigned> cube_back = { 4, 5, 6, 7 };
		std::vector<unsigned> cube_right = { 6, 5, 2, 1 };
		std::vector<unsigned> cube_left = { 0, 3, 4, 7 };
		std::vector<unsigned> cube_bot = { 7, 6, 1, 0 };
		std::vector<unsigned> cube_top = { 2, 3, 4, 5 };
		
		std::vector<Primitive*> primitives;
		primitives.reserve(4 * 8); // 8 cube faces, 4 primitives per face
		
		// add all vertices to buffer
		// and connect vertices
		auto roof_primitives = 
			CreateRoofPrimitives(cube_front, front, 0, false);
		primitives.insert(primitives.end(), roof_primitives.begin(), roof_primitives.end());
		
		roof_primitives = 
			CreateRoofPrimitives(cube_back, back, 0, false);
		primitives.insert(primitives.end(), roof_primitives.begin(), roof_primitives.end());
		
		roof_primitives = 
			CreateRoofPrimitives(cube_left, left, 0, false);
		primitives.insert(primitives.end(), roof_primitives.begin(), roof_primitives.end());
		
		roof_primitives = 
			CreateRoofPrimitives(cube_right, right, 0, false);
		primitives.insert(primitives.end(), roof_primitives.begin(), roof_primitives.end());
		
		roof_primitives = 
			CreateRoofPrimitives(cube_bot, bottom, 0, false);
		primitives.insert(primitives.end(), roof_primitives.begin(), roof_primitives.end());
		
		roof_primitives = 
			CreateRoofPrimitives(cube_top, top, 0, false);
		primitives.insert(primitives.end(), roof_primitives.begin(), roof_primitives.end());

		
		InitBuffers(vertices, primitives);
	}
};
