#ifndef GL_LAB1_RENDERER
#define GL_LAB1_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <glm/vec3.hpp>

#include "Vector3.h"
#include "../Camera.h"

struct ShaderSourceCode {
        std::string Vertex;
        std::string Fragment;
};

class Renderer
{
public:
	Renderer();

	int InitGraphics(int width, int height);
    void LoadShadersFromFile(const std::string& file_path);
	GLFWwindow* get_window() const;
	int get_shader_program() const;
	Camera& get_camera();
	
private:
	Camera main_camera_ = Camera({0, 0, 0}, {0, 0, 0});
	
	GLFWwindow* main_window_;
	unsigned int shader_program_;
	
	ShaderSourceCode ParseShader(const std::string& filePath) const;
	static unsigned int InitShaders(const ShaderSourceCode& code);
	static unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};

#endif
