#include "ProgramInputHandler.h"

#include <thread>
#include <iostream>
#include "Renderer.h"


ProgramInputHandler* ProgramInputHandler::instance_ = nullptr;

Vector3 ProgramInputHandler::window_size = { 0.0, 0.0 };
Renderer ProgramInputHandler::renderer = Renderer();

Vector3* ProgramInputHandler::keyboard_move_dir = new Vector3{ 0.0, 0.0 };
Vector3* ProgramInputHandler::mouse_position = new Vector3{0.0, 0.0};
Vector3* ProgramInputHandler::clicked_position = nullptr;

void (*ProgramInputHandler::additional_callback_) (GLFWwindow* window, int key, int scancode, int action, int mods) = nullptr;

ProgramInputHandler* ProgramInputHandler::GetInstance(const std::string& shader_path, int width, int height)
{
	if (instance_ == nullptr)
	{
		instance_ = new ProgramInputHandler(shader_path, width, height);
	}
	return instance_;
}

ProgramInputHandler::~ProgramInputHandler()
{
	delete mouse_position;
	delete clicked_position;
	delete keyboard_move_dir;
}

ProgramInputHandler::ProgramInputHandler(const std::string& shader_path, int width, int height)
{
	window_size = { static_cast<float>(width), static_cast<float>(height) };
	ProgramInputHandler::shader_path = shader_path;
}

int ProgramInputHandler::RunProgram(ProgramFramework* program)
{
    // create window
    const int err_code = renderer.InitGraphics(
		static_cast<int>(window_size.x), 
		static_cast<int>(window_size.y)
	);

	if (err_code != 0){
        return err_code;
	}

	GLFWwindow* window = renderer.get_window();
	glfwSetKeyCallback(window, CallbackKeyboard);
	glfwSetWindowSizeCallback(window, CallbackWindowResize);
	glfwSetCursorPosCallback(window, CallbackMouseMoved);
	glfwSetMouseButtonCallback(window, CallbackMouseButton);

    renderer.LoadShadersFromFile(shader_path);

	program->Init(this);
	program->previousUpdateTime = glfwGetTime();
	
	while (!glfwWindowShouldClose(GetWindow())) {

		glfwPollEvents();

		if (glfwGetTime() - program->previousUpdateTime < program->desiredUpdateTime)
		{
			continue;
		}

		if (program->Step(this) != 0)
		{
			break;
		}
		
		glfwSwapBuffers(GetWindow());
		program->previousUpdateTime = glfwGetTime();
	}

	glfwTerminate();
	return program->Finish(this);
}

GLFWwindow* ProgramInputHandler::GetWindow()
{
	return renderer.get_window();
}

void ProgramInputHandler::SetKeyboardCallback(
	void(* additional_callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
{
	additional_callback_ = additional_callback;
}

void ProgramInputHandler::CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	const int key_A = glfwGetKey(window, GLFW_KEY_A);
	const int key_D = glfwGetKey(window, GLFW_KEY_D);
	const int key_W = glfwGetKey(window, GLFW_KEY_W);
	const int key_S = glfwGetKey(window, GLFW_KEY_S);

	*keyboard_move_dir = { 0, 0 };

	if (key_A == GLFW_PRESS) {
		keyboard_move_dir->x -= 1;
	}

	if (key_D == GLFW_PRESS) {
		keyboard_move_dir->x += 1;
	}

	// handle up and down
	if (key_W == GLFW_PRESS) {
		keyboard_move_dir->y += 1;
	}

	if (key_S == GLFW_PRESS) {
		keyboard_move_dir->y -= 1;
	}

	keyboard_move_dir->Normalize();

	additional_callback_(window, key, scancode, action, mods);
}

void ProgramInputHandler::CallbackWindowResize(GLFWwindow* window, int width, int height)
{	
	glViewport(0, 0, width, height);
	window_size = { static_cast<float>(width), static_cast<float>(height) };
}

void ProgramInputHandler::CallbackMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		delete clicked_position;

		// convert clicked position to NDC
		clicked_position = new Vector3{
			static_cast<float>(xpos) / window_size.x * 2 - 1,
			static_cast<float>(ypos) / window_size.y * 2 - 1
		};
	}
}

void ProgramInputHandler::CallbackMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	*mouse_position = Vector3{ static_cast<float>(xpos) / window_size.x * 2 - 1, static_cast<float>(ypos) / window_size.x * 2 - 1 };
}
