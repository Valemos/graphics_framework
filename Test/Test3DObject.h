#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

// for console output
#include "Windows.h"
#include <iostream>

#include "Program.h"
#include "draw_objects/Object3D.h"
#include "basic_3d_objects/Sphere.h"
#include "basic_3d_objects/Dodecahedron.h"
#include "basic_3d_objects/AxisObject.h"
#include "math.h"

// for additional key keyboard callback
#include "ButtonHandler.h"
#include "ProgramInputHandler.h"

#define PI (3.141592653589793f)

static const float g_camera_move_speed_ = 0.1;
static float g_increment_zoom_value = 0;


class Test3DObjectsProgram : public Program
{
	const Vector3 object_position_{ 0, 0, 0 };

	ThreeAxis* axis_;
	Object3D* draw_object_;
	
	// camera
	float theta_angle_ = PI / 2;
	float phi_angle_ = 90.f / 180 * PI;
	float radius_ = 8.f;
	Vector3 camera_position_;
	float orthogonal_projection_dimension = 5;

	HANDLE console_handle_;
	
public:
	explicit Test3DObjectsProgram(float fps)
		: Program(fps),
		axis_(nullptr),
		draw_object_(nullptr)
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

	static int HandlePlus(Program*)
	{
		g_increment_zoom_value += g_camera_move_speed_;
		return 0;
	}

	static int HandleMinus(Program*)
	{
		g_increment_zoom_value -= g_camera_move_speed_;
		return 0;
	}

	static int HandlePerspectiveMode(Program*)
	{
		ProgramInputHandler::renderer_light_textured.get_camera().set_draw_mode(DrawMode::Perspective);
		return 0;
	}

	static int HandleOrthogonalMode(Program*)
	{
		ProgramInputHandler::renderer_light_textured.get_camera().set_draw_mode(DrawMode::Orthogonal);
		return 0;
	}

	int Init() override
	{
		// create vertices for primitives
		axis_ = new ThreeAxis();
		axis_->SetPosition({-3, -3, -3});
		
		draw_object_ = new Dodecahedron({ 0.0, 171 / 255.0, 88 / 255.0 }, { 0, 0, 0 });
		draw_object_->Position() = object_position_;

		UpdateCameraSphericalCoordinate();
		ProgramInputHandler::renderer_light_textured.get_camera().UpdateCameraPosition(camera_position_);
		ProgramInputHandler::renderer_light_textured.get_camera().UpdateCameraTarget(draw_object_->Position());
		ProgramInputHandler::renderer_light_textured.get_camera().UpdateCameraUp({0, 1, 0});
		ProgramInputHandler::renderer_light_textured.get_camera().SetOrthoMinimalDimention(orthogonal_projection_dimension);
		
		ProgramInputHandler::SetClearColor(0, 146, 250);
		return 0;
	}

	int Step() override
	{
		const auto keyboard_input = *ProgramInputHandler::keyboard_move_dir;

		if (abs(g_increment_zoom_value) > VECTOR_FLOAT_ACCURACY)
		{
			radius_ += g_increment_zoom_value;
			orthogonal_projection_dimension += g_increment_zoom_value;
			ProgramInputHandler::renderer_light_textured.get_camera().SetOrthoMinimalDimention(orthogonal_projection_dimension);
			UpdateCameraSphericalCoordinate();
			g_increment_zoom_value = 0;
		}
		
		if (keyboard_input.LengthSqr() > VECTOR_FLOAT_ACCURACY)
		{
			phi_angle_ += keyboard_input.x * g_camera_move_speed_;
			theta_angle_ += keyboard_input.y * g_camera_move_speed_;
			UpdateCameraSphericalCoordinate();
		}

		ProgramInputHandler::ClearScreen();
		axis_->Draw(ProgramInputHandler::renderer_light_textured);
		draw_object_->Draw(ProgramInputHandler::renderer_light_textured);
		draw_object_->DrawWireframe(ProgramInputHandler::renderer_light_textured);
		
		SetConsoleCursorPosition(console_handle_, {0, 0});
		std::cout << "pos " << camera_position_.Str() << std::endl;
		return 0;
	}

	void UpdateCameraSphericalCoordinate()
	{
		camera_position_.x = radius_ * sin(theta_angle_) * cos(phi_angle_);
		camera_position_.y = radius_ * cos(theta_angle_);
		camera_position_.z = radius_ * sin(theta_angle_) * sin(phi_angle_);
		ProgramInputHandler::renderer_light_textured.get_camera().UpdateCameraPosition(camera_position_);
	}
};
