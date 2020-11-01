#pragma once

#include "../framework/ProgramFramework.h"
#include "../framework/draw_objects/Object3D.h"
#include "Windows.h"
#include <iostream>
#include "framework/basic_3d_objects/Cube.h"


class Test3DObjectsProgram : public ProgramFramework
{
	const Vector3 cube_position_{ 0, 0, 0 };
	Cube cube_;

	// camera
	const float camera_move_speed_ = 0.1;
	Vector3 camera_position_;

	HANDLE console_handle_;
	
public:
	explicit Test3DObjectsProgram(float fps)
		: ProgramFramework(fps)
	{
		cube_ = Cube(1, { 0.0, 171 / 255.0, 88 / 255.0 }, {0, 0, 0});
	}
	
	int Init(ProgramInputHandler*) override
	{
		// create vertices for primitives
		
		cube_.get_position() = Vector3{ 0, 0, 0 };
		
		camera_position_ = Vector3{ 2.0, 2.0, -2.0 };
		ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
		ProgramInputHandler::renderer.get_camera().UpdateCameraTarget(cube_position_);
		ProgramInputHandler::renderer.get_camera().UpdateCameraUp({0, 1, 0});

		glClearColor(0.0, 146 / 255.0, 250 / 255.0, 1.0);

		console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
		return 0;
	}

	int Step(ProgramInputHandler*) override
	{
		const auto keyboard_input = *ProgramInputHandler::keyboard_move_dir;
		
		if (keyboard_input.Length() > VECTOR_FLOAT_ACCURACY)
		{
			camera_position_ += keyboard_input * camera_move_speed_;
			ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		cube_.DrawWireframe(ProgramInputHandler::renderer);
		SetConsoleCursorPosition(console_handle_, {0, 0});
		std::cout << "pos " << camera_position_.Str() << std::endl;
		
		return 0;
	}
};
