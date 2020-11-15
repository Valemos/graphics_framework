#pragma once

#include "ProgramMultipleObjects.h"

#include <iostream>
#include "math.h"

// for additional key keyboard callback
#include "ProgramInputHandler.h"
#include "ButtonHandler.h"


const float ProgramMultipleObjects::s_camera_move_speed = 0.1;
float ProgramMultipleObjects::s_increment_zoom_value_ = 0;


ProgramMultipleObjects::ProgramMultipleObjects(float fps):
	ProgramFramework(fps), axis_(nullptr), draw_objects_{}
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

int ProgramMultipleObjects::HandlePlus(void*)
{
	s_increment_zoom_value_ -= s_camera_move_speed;
	return 0;
}

int ProgramMultipleObjects::HandleMinus(void*)
{
	s_increment_zoom_value_ += s_camera_move_speed;
	return 0;
}

int ProgramMultipleObjects::HandlePerspectiveMode(void*)
{
	ProgramInputHandler::renderer.get_camera().set_draw_mode(DrawMode::Perspective);
	return 0;
}

int ProgramMultipleObjects::HandleOrthogonalMode(void*)
{
	ProgramInputHandler::renderer.get_camera().set_draw_mode(DrawMode::Orthogonal);
	return 0;
}

float ProgramMultipleObjects::TaskSurfaceFunction(float x, float y) const
{
	return sin(x) * sqrt(y);
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

	for (int y = 0; y < y_count; ++y)
	{
		values[y].resize(x_count, 0);
		for (int x = 0; x < x_count; ++x)
		{
			values[y][x] = TaskSurfaceFunction(x * plot_step, y * plot_step);
		}
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


	UpdateCameraSphericalCoordinate();
	ProgramInputHandler::renderer.get_camera().UpdateCameraTarget({0, 0, 0});
	ProgramInputHandler::renderer.get_camera().UpdateCameraUp(current_camera_up_);
	ProgramInputHandler::renderer.get_camera().SetOrthoMinimalDimention(ortho_projection_dim_);

	ProgramInputHandler::SetClearColor(0, 146, 250);
	return 0;
}

int ProgramMultipleObjects::Step()
{
	const auto keyboard_input = *ProgramInputHandler::keyboard_move_dir;

	if (abs(s_increment_zoom_value_) > VECTOR_FLOAT_ACCURACY)
	{
		radius_ += s_increment_zoom_value_;
		ortho_projection_dim_ += s_increment_zoom_value_;
		s_increment_zoom_value_ = 0;

		// controls zoom in orthogonal projection
		ProgramInputHandler::renderer.get_camera().SetOrthoMinimalDimention(ortho_projection_dim_);
		UpdateCameraSphericalCoordinate();
	}

	bool update_coordinate = false;
	if (abs(keyboard_input.x) > VECTOR_FLOAT_ACCURACY)
	{
		phi_angle_ += keyboard_input.x * s_camera_move_speed;

		if (abs(phi_angle_) - pi2 > VECTOR_FLOAT_ACCURACY)
		{
			phi_angle_ += phi_angle_ < 0 ? pi2 : -pi2;
		}
		update_coordinate = true;
	}

	if (abs(keyboard_input.y) > VECTOR_FLOAT_ACCURACY)
	{
		float prev_theta_angle = theta_angle_;
		theta_angle_ += keyboard_input.y * s_camera_move_speed;

		// modify theta_angle to be in range [0, 2*PI]
		if (theta_angle_ < 0)
		{
			theta_angle_ += pi2;
		}
		else if (theta_angle_ - pi2 > VECTOR_FLOAT_ACCURACY)
		{
			theta_angle_ -= pi2;
		}

		// make next angle the biggest no matter if angle decreases or increases
		float next_theta_angle = theta_angle_;
		if (prev_theta_angle > theta_angle_)
		{
			next_theta_angle = prev_theta_angle;
			prev_theta_angle = theta_angle_;
		}

		// must change up vector when theta passes 0 degrees and 180 degrees
		// to maintain the same orientation relative to center of a scene
		if (prev_theta_angle < bot_angle_ && bot_angle_ < next_theta_angle ||
			prev_theta_angle < top_angle_ && top_angle_ < next_theta_angle)
		{
			current_camera_up_ = current_camera_up_ * -1;
		}

		update_coordinate = true;
	}

	if (update_coordinate)
	{
		UpdateCameraSphericalCoordinate();
		ProgramInputHandler::renderer.get_camera().UpdateCameraUp(current_camera_up_);
	}

	ProgramInputHandler::ClearScreen();

	draw_objects_[0]->Draw(ProgramInputHandler::renderer);
	draw_objects_[1]->Draw(ProgramInputHandler::renderer);
	draw_objects_[2]->DrawWireframe(ProgramInputHandler::renderer);
	draw_objects_[3]->Draw(ProgramInputHandler::renderer);
	draw_objects_[4]->DrawWireframe(ProgramInputHandler::renderer);

	axis_->Draw(ProgramInputHandler::renderer);

	SetConsoleCursorPosition(console_handle_, {0, 0});
	std::cout << "Camera:" << std::endl;
	std::cout << ProgramInputHandler::renderer.get_camera().Str() << std::endl;
	std::cout << "theta: " << theta_angle_ / pi * 180 << "\tphi: " << phi_angle_ / pi * 180 << std::endl;
	std::cout << "camera up: " << current_camera_up_.Str() << std::endl;
	return 0;
}

void ProgramMultipleObjects::UpdateCameraSphericalCoordinate()
{
	camera_position_.x = radius_ * sin(theta_angle_) * cos(phi_angle_);
	camera_position_.z = radius_ * sin(theta_angle_) * sin(phi_angle_);
	camera_position_.y = radius_ * cos(theta_angle_);
	ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
}
