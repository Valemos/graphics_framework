#pragma once

#include "Windows.h"
#include <iostream>

#include "math.h"
#include "../framework/ProgramInputHandler.h"
#include "../framework/ProgramFramework.h"
#include "../framework/draw_objects/Object3D.h"
#include "../framework/basic_3d_objects/Sphere.h"
#include "../framework/basic_3d_objects/Dodecahedron.h"

#include "basic_3d_objects/Sphere.h"
#include "basic_3d_objects/Dodecahedron.h"
#include "basic_3d_objects/Surface.h"
#include "basic_3d_objects/AxisObject.h"

// for additional key keyboard callback
#include "GL/glew.h"
#include "GLFW/glfw3.h"

static constexpr float pi = 3.141592653589793f;
static constexpr float pi2 = pi * 2;

static const float g_camera_move_speed_ = 0.1;

// GLFW requires static handler functions, thus also static variables to be modified
// I could have used the same upproach with keys "+" "-" as with "W", "A", "S" and "D",
// (i. e. move key handling to ProgramInputHandler)
// but using global variable were faster
// this can be improved if necessary
static float g_increment_zoom_value = 0;


class ProgramLab2 : public ProgramFramework
{
	// to reset console
	HANDLE console_handle_;
	
	ThreeAxis* axis_;
	Object3D* draw_objects_[5];

	// camera
	const float top_angle_ = 0.f;
	const float bot_angle_ = pi;
	float theta_angle_ = 90.f / 180 * pi;
	float phi_angle_ = 90.f / 180 * pi;
	float radius_ = 20.f;
	
	Vector3 camera_position_;
	Vector3 camera_up_{ 0, 1, 0 };
	Vector3 camera_down_{ 0, -1, 0 };
	Vector3 current_camera_up_ = camera_up_;

	// controls zoom when in orthogonal mode
	float ortho_projection_dim_ = radius_;

public:
	explicit ProgramLab2(float fps)
		: ProgramFramework(fps), axis_(nullptr), draw_objects_{}
	{
		console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
		ProgramInputHandler::SetKeyboardCallback(keyboard_callback);
	}

	static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
			// radius increments
			zoom_value += 1;
		}
		if (key_plus == GLFW_PRESS)
		{
			// radius decrements
			zoom_value -= 1;
		}

		if (zoom_value != 0)
		{
			g_increment_zoom_value = zoom_value * g_camera_move_speed_;
		}
	}

	float task_surface_function(float x, float y)
	{
		return sin(x) * sqrt(y);
	}

	int Init(ProgramInputHandler*) override
	{
		axis_ = new ThreeAxis();
		axis_->SetPosition({-5, 0, -5});
		axis_->SetScale({ 2, 2, 2 });
		
		// create vertices for primitives
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
				values[y][x] = task_surface_function(x * plot_step, y * plot_step);
			}
		}

		draw_objects_[0] = new Surface(values, { 0.0, 171 / 255.0, 88 / 255.0 }, { 0, 0, 0 });
		draw_objects_[0]->Position() = Vector3{0, 0, 0};
		draw_objects_[0]->figure_scale.y = 0.5;

		draw_objects_[1] = new Sphere({ 252 / 255.f, 198 / 255.f, 0.f }, { 0, 0, 0 });
		draw_objects_[1]->Position() = Vector3{2, 4, 0};

		draw_objects_[2] = new Sphere({ 252 / 255.f, 198 / 255.f, 0.f }, { 0, 0, 0 });
		draw_objects_[2]->Position() = Vector3{-2, 4, 0};

		draw_objects_[3] = new Dodecahedron({ 252 / 255.f, 0.f, 98 / 255.f }, { 0, 0, 0 });
		draw_objects_[3]->Position() = Vector3{2, -4, 0};
		
		draw_objects_[4] = new Dodecahedron({ 252 / 255.f, 0.f, 98 / 255.f }, { 0, 0, 0 });
		draw_objects_[4]->Position() = Vector3{-2, -4, 0};
		
		
		UpdateCameraSphericalCoordinate();
		ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
		ProgramInputHandler::renderer.get_camera().UpdateCameraTarget({0, 0, 0});
		ProgramInputHandler::renderer.get_camera().UpdateCameraUp(current_camera_up_);
		ProgramInputHandler::renderer.get_camera().set_ortho_minimal_dimention(ortho_projection_dim_);

		glClearColor(0.0, 146 / 255.0, 250 / 255.0, 1.0);
		return 0;
	}

	int Step(ProgramInputHandler*) override
	{
		const auto keyboard_input = *ProgramInputHandler::keyboard_move_dir;

		if (abs(g_increment_zoom_value) > VECTOR_FLOAT_ACCURACY)
		{
			radius_ += g_increment_zoom_value;
			ortho_projection_dim_ += g_increment_zoom_value;
			g_increment_zoom_value = 0;

			// controls zoom in orthogonal projection
			ProgramInputHandler::renderer.get_camera().set_ortho_minimal_dimention(ortho_projection_dim_);
			UpdateCameraSphericalCoordinate();
		}

		bool update_coordinate = false;
		if (abs(keyboard_input.x) > VECTOR_FLOAT_ACCURACY)
		{
			phi_angle_ += keyboard_input.x * g_camera_move_speed_;

			if (abs(phi_angle_) - pi2 > VECTOR_FLOAT_ACCURACY)
			{
				phi_angle_ += phi_angle_ < 0 ? pi2 : -pi2;
			}
			update_coordinate = true;
		}

		if (abs(keyboard_input.y) > VECTOR_FLOAT_ACCURACY)
		{
			float prev_theta_angle = theta_angle_;
			theta_angle_ += keyboard_input.y * g_camera_move_speed_;

			// modify theta_angle to be in range [0, 2*PI]
			if (theta_angle_ < 0)
			{
				theta_angle_ += pi2;
			}
			
			if (theta_angle_ - pi2 > VECTOR_FLOAT_ACCURACY)
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
			if ((prev_theta_angle < bot_angle_ && bot_angle_ < next_theta_angle) ||
				(prev_theta_angle < top_angle_ && top_angle_ < next_theta_angle))
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
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_objects_[0]->Draw(ProgramInputHandler::renderer);
		draw_objects_[1]->Draw(ProgramInputHandler::renderer);
		draw_objects_[2]->DrawWireframe(ProgramInputHandler::renderer);
		draw_objects_[3]->Draw(ProgramInputHandler::renderer);
		draw_objects_[4]->DrawWireframe(ProgramInputHandler::renderer);

		axis_->Draw(ProgramInputHandler::renderer);
		
		SetConsoleCursorPosition(console_handle_, { 0, 0 });
		std::cout << "Camera:" << std::endl;
		std::cout << ProgramInputHandler::renderer.get_camera().Str() << "                    " << std::endl;
		std::cout << "theta: " << theta_angle_ / pi * 180 << "\tphi: " << phi_angle_ / pi * 180 << "                    " << std::endl;
		std::cout << "camera up: " << current_camera_up_.Str() << "                    " << std::endl;
		return 0;
	}

	void UpdateCameraSphericalCoordinate()
	{
		camera_position_.x = radius_ * sin(theta_angle_) * cos(phi_angle_);
		camera_position_.z = radius_ * sin(theta_angle_) * sin(phi_angle_);
		camera_position_.y = radius_ * cos(theta_angle_);
		ProgramInputHandler::renderer.get_camera().UpdateCameraPosition(camera_position_);
	}
};

int main()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance("D:/coding/c_c++/SimpleGraphicalFramework/Framework/framework/shaders/main_shaders.shader", 800, 600);
	return program->RunProgram(new ProgramLab2(60.f));
}
