#pragma once

#include "Windows.h"
#include <iostream>

#include "../framework/ProgramFramework.h"
#include "../framework/draw_objects/Object3D.h"
#include "../framework/basic_3d_objects/Sphere.h"
#include "../framework/basic_3d_objects/Cube.h"
#include "../framework/basic_3d_objects/Dodecahedron.h"
#include "math.h"

// for additional key keyboard callback
#include "../framework/basic_3d_objects/AxisObject.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define PI (3.141592653589793)

static const float g_camera_move_speed_ = 0.1;
static float g_increment_zoom_value = 0;

class Test3DObjectsProgram : public ProgramFramework
{
	const Vector3 object_position_{ 0, 0, 0 };

	ThreeAxis* axis_;
	Object3D* draw_object_;
	
	// camera
	float theta_angle_ = 90.f / 180 * PI;
	float phi_angle_ = 0.f;
	float radius_ = 5.f;
	Vector3 camera_position_;
	float orthogonal_projection_dimention = 5;

	HANDLE console_handle_;
	
public:
	explicit Test3DObjectsProgram(float fps)
		: ProgramFramework(fps),
		draw_object_(nullptr),
		axis_(nullptr)
	{
		console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
		ProgramInputHandler::SetKeyboardCallback(keyboard_callback);
	}

	static void keyboard_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// + - to zoom in and out

		const int key_plus = glfwGetKey(window, GLFW_KEY_EQUAL);
		const int key_minus = glfwGetKey(window, GLFW_KEY_MINUS);

		const int key_p = glfwGetKey(window, GLFW_KEY_P);
		const int key_o = glfwGetKey(window, GLFW_KEY_O);
		
		if (key_p == GLFW_PRESS)
		{
			ProgramInputHandler::renderer.get_camera().set_draw_mode(Perspective);
		}
		else if (key_o == GLFW_PRESS)
		{
			ProgramInputHandler::renderer.get_camera().set_draw_mode(Orthogonal);
		}

		int zoom_value = 0;
		if (key_minus == GLFW_PRESS)
		{
			zoom_value -= 1;
		}
		if (key_plus == GLFW_PRESS)
		{
			zoom_value += 1;
		}

		if (zoom_value != 0)
		{
			g_increment_zoom_value = zoom_value * g_camera_move_speed_;
		} 
	}
	
	int Init(ProgramInputHandler*) override
	{
		// create vertices for primitives
		axis_ = new ThreeAxis();
		
		draw_object_ = new Dodecahedron({ 0.0, 171 / 255.0, 88 / 255.0 }, { 0, 0, 0 });
		draw_object_->Position() = object_position_;

		UpdateCameraSphericalCoordinate();
		ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
		ProgramInputHandler::renderer.get_camera().UpdateCameraTarget(draw_object_->Position());
		ProgramInputHandler::renderer.get_camera().UpdateCameraUp({0, 1, 0});
		ProgramInputHandler::renderer.get_camera().set_ortho_minimal_dimention(orthogonal_projection_dimention);
		
		glClearColor(0.0, 146 / 255.0, 250 / 255.0, 1.0);
		return 0;
	}

	int Step(ProgramInputHandler*) override
	{
		const auto keyboard_input = *ProgramInputHandler::keyboard_move_dir;

		if (abs(g_increment_zoom_value) > VECTOR_FLOAT_ACCURACY)
		{
			radius_ += g_increment_zoom_value;
			orthogonal_projection_dimention += g_increment_zoom_value;
			ProgramInputHandler::renderer.get_camera().set_ortho_minimal_dimention(orthogonal_projection_dimention);
			UpdateCameraSphericalCoordinate();
			g_increment_zoom_value = 0;
		}
		
		if (keyboard_input.LengthSqr() > VECTOR_FLOAT_ACCURACY)
		{
			phi_angle_ += keyboard_input.x * g_camera_move_speed_;
			theta_angle_ += keyboard_input.y * g_camera_move_speed_;
			UpdateCameraSphericalCoordinate();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		axis_->Draw(ProgramInputHandler::renderer);
		draw_object_->DrawWireframe(ProgramInputHandler::renderer);
		
		SetConsoleCursorPosition(console_handle_, {0, 0});
		std::cout << "pos " << camera_position_.Str() << std::endl;
		return 0;
	}

	void UpdateCameraSphericalCoordinate()
	{
		camera_position_.x = radius_ * sin(theta_angle_) * cos(phi_angle_);
		camera_position_.y = radius_ * cos(theta_angle_);
		camera_position_.z = radius_ * sin(theta_angle_) * sin(phi_angle_);
		ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
	}
};
