#ifndef GL_LAB1_INPUT_HANDLER
#define GL_LAB1_INPUT_HANDLER


#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Vector3.h"
#include "Renderer.h"
#include "Program.h"
#include <vector>
#include "ButtonHandler.h"


class ProgramInputHandler
{

public:
	// we store previous window size to rescale images with global scale
	static Vector3 window_size;
	static Vector3* clicked_position;
	static Vector3* mouse_position;
	static Vector3* keyboard_move_dir;
	static std::vector<ButtonHandler> button_handlers;
	static const std::vector<ButtonHandler> default_handlers;
	static Renderer renderer;

	~ProgramInputHandler();

	static void ClearScreen();
	static void SetClearColor(int r, int g, int b, int a = 255);
	
	static int RunProgram(Program*, const std::string& shader_path, int width = 100, int height = 100);
	
	static GLFWwindow* GetWindow();
	static void CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void AddButtonHandlers(std::vector<ButtonHandler> handlers);
	static int HandleButtons(Program* program);
	
	static void RemoveButtonHandlers(std::vector<Key>& key_types);
    static void CallbackWindowResize(GLFWwindow* window, int width, int height);
	static void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void CallbackMouseMoved(GLFWwindow* window, double xpos, double ypos);
	static void APIENTRY CallbackGlError(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	
private:
	static GLFWwindow* main_window_;
};

#endif // !GL_LAB1_INPUT_HANDLER
