#include "ProgramInputHandler.h"

#include <thread>
#include <iostream>
#include <vector>
#include "Renderer.h"

GLFWwindow* ProgramInputHandler::main_window_ = nullptr;
Vector3 ProgramInputHandler::window_size = { 0.0, 0.0 };
Renderer ProgramInputHandler::renderer = Renderer();

Vector3* ProgramInputHandler::mouse_position = new Vector3{0.0, 0.0};
Vector3* ProgramInputHandler::clicked_position = nullptr;

Vector3* ProgramInputHandler::keyboard_move_dir = new Vector3{ 0.0, 0.0 };

// default button handlers

static int default_handler_w(Program* program)
{
	ProgramInputHandler::keyboard_move_dir->y += 1;
	return 0;
};

static int default_handler_s(Program*)
{
	ProgramInputHandler::keyboard_move_dir->y -= 1;
	return 0;
};

static int default_handler_a(Program*)
{
	ProgramInputHandler::keyboard_move_dir->x -= 1;
	return 0;
};

static int default_handler_d(Program* program)
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


ProgramInputHandler::~ProgramInputHandler()
{
	delete mouse_position;
	delete clicked_position;
	delete keyboard_move_dir;
}

int ProgramInputHandler::RunProgram(Program* program, const std::string& shader_path, int width, int height)
{
	window_size = { static_cast<float>(width), static_cast<float>(height) };

    // create window
	if (!glfwInit()) {
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	main_window_ = glfwCreateWindow(static_cast<int>(window_size.x), static_cast<int>(window_size.y), program->window_name.c_str(), NULL, NULL);
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

	// init debug callback
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(CallbackGlError, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	
	glfwSetKeyCallback(main_window_, CallbackKeyboard);
	glfwSetWindowSizeCallback(main_window_, CallbackWindowResize);
	glfwSetCursorPosCallback(main_window_, CallbackMouseMoved);
	glfwSetMouseButtonCallback(main_window_, CallbackMouseButton);

    renderer.LoadShadersFromFile(shader_path);

	glEnable(GL_DEPTH_TEST);
	
	glViewport(0, 0, static_cast<int>(window_size.x), static_cast<int>(window_size.y));

	// enter program loop
	bool program_restart = false;
	do
	{
		program->Init();
		program->previous_update_time = glfwGetTime();

		while (!glfwWindowShouldClose(GetWindow())) {

			glfwPollEvents();

			if (glfwGetTime() - program->previous_update_time < program->desired_update_time)
			{
				continue;
			}

			ClearScreen();
			const int return_code = program->Step();

			// decide what to do with return code
			if (return_code == Program::program_continue)
			{
				glfwSwapBuffers(GetWindow());
				program->previous_update_time = glfwGetTime();
			}
			else if (return_code == Program::program_restart)
			{
				program_restart = true;
				program->Finish();
				break;
			}
			else if (return_code == Program::program_finish)
			{
				program_restart = false;
				break;
			}
		}
	} while (program_restart && !glfwWindowShouldClose(GetWindow()));

	program->Finish();
	glfwTerminate();

	return Program::program_continue;
}

void ProgramInputHandler::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ProgramInputHandler::SetClearColor(int r, int g, int b, int a)
{
	glClearColor((float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f);
}

GLFWwindow* ProgramInputHandler::GetWindow()
{
	return main_window_;
}

void ProgramInputHandler::CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto& handler : button_handlers)
	{
		const int key_status = glfwGetKey(window, static_cast<int>(handler.GetType()));
		if (key_status == GLFW_PRESS)
		{
			handler.SetButtonState(true);
		}
	}
}

void ProgramInputHandler::AddButtonHandlers(std::vector<ButtonHandler> handlers)
{
	button_handlers.insert(button_handlers.end(), handlers.begin(), handlers.end());
}

int ProgramInputHandler::HandleButtons(Program* program)
{
	*keyboard_move_dir = { 0, 0 };
	auto return_code = Program::program_continue;

	for (auto& handler : button_handlers)
	{
		if (handler.GetButtonState())
		{
			const auto new_code = handler.Handle(program);
			return_code = new_code != Program::program_continue ? new_code : return_code;
			
			handler.SetButtonState(false);
		}
	}
	
	keyboard_move_dir->Normalize();
	return return_code;
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
			}
			else
			{
				++it_key;
			}
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
	const auto global_scale = renderer.GetGlobalScale();
	*mouse_position = {
		(static_cast<float>(xpos) / window_size.x * 2 - 1) / global_scale.x,
		(-static_cast<float>(ypos) / window_size.y * 2 + 1) / global_scale.y
	};
}

void APIENTRY ProgramInputHandler::CallbackGlError(GLenum source, GLenum type, unsigned id, GLenum severity, GLsizei length,
	const char* message, const void* userParam)
{

	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
		case GL_DEBUG_SOURCE_API:				std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:	std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:		std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:		std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:				std::cout << "Source: Other"; break;
		default:								std::cout << "Source: No source"; break;
	}
	std::cout << std::endl;

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
		default:								std::cout << "Type: No type"; break;
	}
	std::cout << std::endl;

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:			std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:			std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:				std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	std::cout << "Severity: notification"; break;
		default:								std::cout << "Severity: No severity"; break;
	}
	std::cout << std::endl << std::endl;
}
