#include "ProgramInputHandler.h"

#include <thread>
#include <iostream>
#include <vector>
#include "Renderer.h"


ProgramInputHandler* ProgramInputHandler::instance_ = nullptr;

GLFWwindow* ProgramInputHandler::main_window_ = nullptr;
Vector3 ProgramInputHandler::window_size = { 0.0, 0.0 };
Renderer ProgramInputHandler::renderer = Renderer();

Vector3* ProgramInputHandler::mouse_position = new Vector3{0.0, 0.0};
Vector3* ProgramInputHandler::clicked_position = nullptr;

Vector3* ProgramInputHandler::keyboard_move_dir = new Vector3{ 0.0, 0.0 };

// default button handlers

static int default_handler_w(void*)
{
	ProgramInputHandler::keyboard_move_dir->y += 1;
	return 0;
};

static int default_handler_s(void*)
{
	ProgramInputHandler::keyboard_move_dir->y -= 1;
	return 0;
};

static int default_handler_a(void*)
{
	ProgramInputHandler::keyboard_move_dir->x -= 1;
	return 0;
};

static int default_handler_d(void*)
{
	ProgramInputHandler::keyboard_move_dir->x += 1;
	return 0;
};

const std::vector<ButtonHandler> ProgramInputHandler::default_handlers = {
	ButtonHandler(Key::W, default_handler_w),
	ButtonHandler(Key::A, default_handler_a),
	ButtonHandler(Key::S, default_handler_s),
	ButtonHandler(Key::D, default_handler_d)
};

std::vector<ButtonHandler> ProgramInputHandler::button_handlers(
	default_handlers.begin(), 
	default_handlers.end());

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

ProgramInputHandler::ProgramInputHandler(const std::string& path, int width, int height)
{
	window_size = { static_cast<float>(width), static_cast<float>(height) };
	shader_path = path;
}

int ProgramInputHandler::RunProgram(ProgramFramework* program)
{
    // create window
	if (!glfwInit()) {
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	main_window_ = glfwCreateWindow(static_cast<int>(window_size.x), static_cast<int>(window_size.y), "Figure", NULL, NULL);
	if (!main_window_)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(main_window_);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return -1;
	}

	glViewport(0, 0, static_cast<int>(window_size.x), static_cast<int>(window_size.y));
	
	glfwSetKeyCallback(main_window_, CallbackKeyboard);
	glfwSetWindowSizeCallback(main_window_, CallbackWindowResize);
	glfwSetCursorPosCallback(main_window_, CallbackMouseMoved);
	glfwSetMouseButtonCallback(main_window_, CallbackMouseButton);

    renderer.LoadShadersFromFile(shader_path);

	glEnable(GL_DEPTH_TEST);
	
	program->Init();
	program->previousUpdateTime = glfwGetTime();
	
	while (!glfwWindowShouldClose(GetWindow())) {

		glfwPollEvents();

		if (glfwGetTime() - program->previousUpdateTime < program->desiredUpdateTime)
		{
			continue;
		}

		if (program->Step() != 0)
		{
			break;
		}
		
		glfwSwapBuffers(GetWindow());
		program->previousUpdateTime = glfwGetTime();
	}

	glfwTerminate();
	return program->Finish();
}

GLFWwindow* ProgramInputHandler::GetWindow()
{
	return main_window_;
}

void ProgramInputHandler::CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	*keyboard_move_dir = { 0, 0 };

	for (auto handler : button_handlers)
	{
		const int key_status = glfwGetKey(window, static_cast<int>(handler.GetType()));
		if (key_status == GLFW_PRESS)
		{
			if (handler.Handle() != 0)
			{
				std::cout << "button " << static_cast<int>(handler.GetType()) << "unhandled" << std::endl;
			}
		}
	}

	keyboard_move_dir->Normalize();
}

void ProgramInputHandler::AddButtonHandlers(std::vector<ButtonHandler>& handlers)
{
	button_handlers.insert(button_handlers.end(), handlers.begin(), handlers.end());
}

void ProgramInputHandler::RemoveButtonHandlers(std::vector<Key>& key_types)
{
	auto new_handlers = std::vector<ButtonHandler>();
	new_handlers.reserve(button_handlers.size());
	for (auto it_handler = button_handlers.begin(); it_handler != button_handlers.end();)
	{
		for (auto it_key = key_types.begin(); it_key != key_types.end();)
		{
			if (it_handler->GetType() == *it_key)
			{
				button_handlers.erase(it_handler);
				key_types.erase(it_key);
				break;
			}
			++it_key;
		}
		++it_handler;
	}
}

void ProgramInputHandler::CallbackWindowResize(GLFWwindow* window, int width, int height)
{	
	glViewport(0, 0, width, height);

	const auto prev_scale = renderer.GetGlobalScale();
	renderer.SetGlobalScale({
		prev_scale.x * window_size.x / width, 
		prev_scale.y * window_size.y / height,
		prev_scale.z
	});
	
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
			static_cast<float>(ypos) / window_size.y * 2 - 1,
			0
		};
	}
}

void ProgramInputHandler::CallbackMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	*mouse_position = Vector3{ static_cast<float>(xpos) / window_size.x * 2 - 1, static_cast<float>(ypos) / window_size.x * 2 - 1 };
}
