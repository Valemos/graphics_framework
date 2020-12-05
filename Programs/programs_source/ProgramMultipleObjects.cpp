#pragma once

#include "ProgramMultipleObjects.h"

#include <iostream>

// for additional key keyboard callback
#include "ProgramInputHandler.h"
#include "ButtonHandler.h"


SphericalCamera* ProgramMultipleObjects::s_camera_controller_ = nullptr;
bool ProgramMultipleObjects::s_update_camera_ = false;

ProgramMultipleObjects::ProgramMultipleObjects(float fps):
	Program(fps), axis_(nullptr), draw_objects_{}
{
	console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE);

	auto handlers = std::vector<ButtonHandler>{
		ButtonHandler(Key::Equal, HandlePlus),
		ButtonHandler(Key::Minus, HandleMinus),
		ButtonHandler(Key::P, HandlePerspectiveMode),
		ButtonHandler(Key::O, HandleOrthogonalMode)
	};
	ProgramInputHandler::AddButtonHandlers(handlers);
}

float ProgramMultipleObjects::TaskSurfaceFunction(float x, float y)
{
    return sin(x) * sqrt(y);
}

Program::ProgramState ProgramMultipleObjects::HandlePlus(Program*)
{
    if (s_camera_controller_ != nullptr) {
        s_camera_controller_->DecrementRadius();
        s_update_camera_ = true;
    }
	return program_continue;
}

Program::ProgramState ProgramMultipleObjects::HandleMinus(Program*)
{
    if (s_camera_controller_ != nullptr){
        s_camera_controller_->IncrementRadius();
        s_update_camera_ = true;
    }
	return program_continue;
}

Program::ProgramState ProgramMultipleObjects::HandlePerspectiveMode(Program*)
{
    s_camera_controller_->get_camera().set_draw_mode(DrawMode::Perspective);
	return program_continue;
}

Program::ProgramState ProgramMultipleObjects::HandleOrthogonalMode(Program*)
{
	s_camera_controller_->get_camera().set_draw_mode(DrawMode::Orthogonal);
	return program_continue;
}

int ProgramMultipleObjects::Init()
{
	axis_ = new ThreeAxis();
	axis_->SetPosition({-5, 0, -5});
	axis_->SetScale({2, 2, 2});

	// create values for Surface object
	const float plot_step = 0.1f;
	const int x_count = 50;
	const int y_count = 50;

	std::vector<std::vector<float>> values;
	values.resize(y_count);

	for (float y = 0; y < y_count;)
	{
		values[y].resize(x_count, 0);
		for (float x = 0; x < x_count;)
		{
			values[y][x] = TaskSurfaceFunction(x * plot_step, y * plot_step);
            x += 1.f;
		}
        y += 1.f;
	}

	draw_objects_[0] = new Surface(values, {0.0, 171 / 255.0, 88 / 255.0}, {0, 0, 0});
	draw_objects_[0]->Position() = Vector3{0, 0, 0};
	draw_objects_[0]->figure_scale.y = 0.5;

	
	draw_objects_[1] = new Sphere({252 / 255.f, 198 / 255.f, 0.f}, {0, 0, 0});
	draw_objects_[1]->Position() = Vector3{2, 4, 0};

	draw_objects_[2] = new Sphere({252 / 255.f, 198 / 255.f, 0.f}, {0, 0, 0});
	draw_objects_[2]->Position() = Vector3{-2, 4, 0};

	draw_objects_[3] = new Dodecahedron({252 / 255.f, 0.f, 98 / 255.f}, {0, 0, 0});
	draw_objects_[3]->Position() = Vector3{2, -4, 0};

	draw_objects_[4] = new Dodecahedron({252 / 255.f, 0.f, 98 / 255.f}, {0, 0, 0});
	draw_objects_[4]->Position() = Vector3{-2, -4, 0};


    s_camera_controller_ = new SphericalCamera(
            {0, 0, -5},
            {0, 0, 0},
            {0, 1, 0},
            0.1, 0, 0);

	ProgramInputHandler::SetClearColor(0, 146, 250);
	return 0;
}

int ProgramMultipleObjects::Step()
{
	const auto keyboard_input = *ProgramInputHandler::keyboard_move_dir;

	if (s_update_camera_)
	{
	    // update if zoomed and not updated during move
        s_camera_controller_->UpdatePosition();
        s_update_camera_ = false;
	}

    s_camera_controller_->MoveCamera(keyboard_input);


	ProgramInputHandler::ClearScreen();

	draw_objects_[0]->Draw(ProgramInputHandler::renderer_light_textured);
	draw_objects_[1]->Draw(ProgramInputHandler::renderer_light_textured);
	draw_objects_[2]->DrawWireframe(ProgramInputHandler::renderer_light_textured);
	draw_objects_[3]->Draw(ProgramInputHandler::renderer_light_textured);
	draw_objects_[4]->DrawWireframe(ProgramInputHandler::renderer_light_textured);

	axis_->Draw(ProgramInputHandler::renderer_light_textured);

	SetConsoleCursorPosition(console_handle_, {0, 0});
	std::cout << "Camera:" << std::endl;
	std::cout << ProgramInputHandler::renderer_light_textured.get_camera().Str() << std::endl;
	return 0;
}
