#pragma once

#include "../framework/ProgramFramework.h"
#include "../framework/draw_objects/Object3D.h"

class Test3DObjectsProgram : public ProgramFramework
{
	const Vector3 cube_position{ 0, 0, 0 };
	Object3D cube;
	
public:
	explicit Test3DObjectsProgram(float fps)
		: ProgramFramework(fps)
	{
		cube = Object3D();
	}
	
	int Init(ProgramInputHandler*) override
	{
		// create vertices for primitives
		cube.surface_color = { 0.0, 69 / 255.0, 1.0 };
		cube.figure_scale = { 1, 1, 1 };

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
		cube.InitBuffers(
			cube_vertices,
		{
			new Quad({0, 1, 2, 3}),
			new Quad({4, 5, 6, 7}),
			new Quad({6, 5, 2, 1}),
			new Quad({0, 3, 4, 7}),
			new Quad({7, 6, 1, 0}),
			new Quad({2, 3, 4, 5})
		});

		ProgramInputHandler::renderer.get_camera().UpdateCameraPosition({1.0, 1.0, -2.0});
		ProgramInputHandler::renderer.get_camera().UpdateCameraTarget({ 0, 0, 0 });
		
		return 0;
	}

	int Step(ProgramInputHandler*) override
	{
		cube.Draw(ProgramInputHandler::renderer, cube_position);
		return 0;
	}
};
