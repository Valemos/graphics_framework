#ifndef GL_LAB1_INPUT_HANDLER
#define GL_LAB1_INPUT_HANDLER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Vector3.h"
#include "Renderer.h"
#include "ProgramFramework.h"


class ProgramInputHandler
{
public:
	static Vector3* clicked_position;
	static Vector3* mouse_position;
	static Vector3* keyboard_move_dir;
	static Renderer renderer;
	std::string shader_path;

	static ProgramInputHandler* GetInstance(const std::string& shader_path, int width, int height);
	~ProgramInputHandler();

	int RunProgram(ProgramFramework*);
	static GLFWwindow* GetWindow();
	static void CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void CallbackWindowResize(GLFWwindow* window, int width, int height);
	static void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void CallbackMouseMoved(GLFWwindow* window, double xpos, double ypos);
	
private:
	static ProgramInputHandler* instance_;
	ProgramInputHandler(const std::string& shader_path, int width, int height);

	// we store previous window size to rescale images with global scale
	static Vector3 window_size_;
};


#endif // !GL_LAB1_INPUT_HANDLER
