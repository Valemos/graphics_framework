#include "ProgramInputHandler.h"

#include <thread>
#include <iostream>
#include <vector>
#include "Renderer.h"

GLFWwindow* ProgramInputHandler::main_window_ = nullptr;
Vector3 ProgramInputHandler::window_size_ = { 0.0, 0.0 };
Renderer ProgramInputHandler::renderer_ = Renderer();

Vector3* ProgramInputHandler::mouse_position_ = new Vector3{0.0, 0.0};
Vector3* ProgramInputHandler::clicked_position_ = nullptr;

Vector3* ProgramInputHandler::keyboard_move_dir_ = new Vector3{ 0.0, 0.0 };

// default button handlers

static int default_handler_w(void*)
{
	ProgramInputHandler::keyboard_move_dir_->y += 1;
	return 0;
};

static int default_handler_s(void*)
{
	ProgramInputHandler::keyboard_move_dir_->y -= 1;
	return 0;
};

static int default_handler_a(void*)
{
	ProgramInputHandler::keyboard_move_dir_->x -= 1;
	return 0;
};

static int default_handler_d(void*)
{
	ProgramInputHandler::keyboard_move_dir_->x += 1;
	return 0;
};

const std::vector<ButtonHandler> ProgramInputHandler::default_handlers = {
	ButtonHandler(Key::W, default_handler_w),
	ButtonHandler(Key::A, default_handler_a),
	ButtonHandler(Key::S, default_handler_s),
	ButtonHandler(Key::D, default_handler_d)
};

std::vector<ButtonHandler> ProgramInputHandler::button_handlers_(
	default_handlers.begin(), 
	default_handlers.end());


ProgramInputHandler::~ProgramInputHandler()
{
	delete mouse_position_;
	delete clicked_position_;
	delete keyboard_move_dir_;
}

int ProgramInputHandler::RunProgram(Program* program, const std::string& shader_path, int width, int height)
{
	window_size_ = { static_cast<float>(width), static_cast<float>(height) };

    // create window
	if (!glfwInit()) {
		return -1;
	}

	
	/* Create a windowed mode window and its OpenGL context */
	main_window_ = glfwCreateWindow(static_cast<int>(window_size_.x), static_cast<int>(window_size_.y), "Program", NULL, NULL);
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

    renderer_.LoadShadersFromFile(shader_path);

	glEnable(GL_DEPTH_TEST);
	
	glViewport(0, 0, static_cast<int>(window_size_.x), static_cast<int>(window_size_.y));
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

void ProgramInputHandler::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ProgramInputHandler::SetClearColor(double r, double g, double b, double a)
{
	glClearColor(r, g, b, a);
}

void ProgramInputHandler::SetClearColor(int r, int g, int b, int a)
{
	glClearColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

GLFWwindow* ProgramInputHandler::GetWindow()
{
	return main_window_;
}

void ProgramInputHandler::CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	*keyboard_move_dir_ = { 0, 0 };

	for (auto handler : button_handlers_)
	{
		const int key_status = glfwGetKey(window, static_cast<int>(handler.GetType()));
		if (key_status == GLFW_PRESS)
		{
			if (handler.Handle() != 0)
			{
				std::cout << "button " << static_cast<int>(handler.GetType()) << " unhandled" << std::endl;
			}
		}
	}

	keyboard_move_dir_->Normalize();
}

void ProgramInputHandler::AddButtonHandlers(std::vector<ButtonHandler>& handlers)
{
	button_handlers_.insert(button_handlers_.end(), handlers.begin(), handlers.end());
}

void ProgramInputHandler::RemoveButtonHandlers(std::vector<Key>& key_types)
{
	auto new_handlers = std::vector<ButtonHandler>();
	new_handlers.reserve(button_handlers_.size());
	for (auto it_handler = button_handlers_.begin(); it_handler != button_handlers_.end();)
	{
		for (auto it_key = key_types.begin(); it_key != key_types.end();)
		{
			if (it_handler->GetType() == *it_key)
			{
				button_handlers_.erase(it_handler);
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

	const auto prev_scale = renderer_.GetGlobalScale();
	renderer_.SetGlobalScale({
		prev_scale.x * window_size_.x / width, 
		prev_scale.y * window_size_.y / height,
		prev_scale.z
	});
	
	window_size_ = { static_cast<float>(width), static_cast<float>(height) };
}

void ProgramInputHandler::CallbackMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		delete clicked_position_;

		// convert clicked position to NDC
		clicked_position_ = new Vector3{
			static_cast<float>(xpos) / window_size_.x * 2 - 1,
			static_cast<float>(ypos) / window_size_.y * 2 - 1,
			0
		};
	}
}

void ProgramInputHandler::CallbackMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	*mouse_position_ = Vector3{ static_cast<float>(xpos) / window_size_.x * 2 - 1, static_cast<float>(ypos) / window_size_.x * 2 - 1 };
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
