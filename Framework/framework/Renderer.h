#ifndef GL_LAB1_RENDERER
#define GL_LAB1_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <glm/vec3.hpp>

#include "Vector3.h"

struct ShaderSourceCode {
        std::string Vertex;
        std::string Fragment;
};

class Renderer
{
public:
	Renderer();

	int InitGraphics(int width, int height);
	GLFWwindow* GetWindow() const;
    void LoadShadersFromFile(const std::string& file_path);
	int GetShaderProgram() const;
	glm::vec3 GetScaleForGL() const;
	Vector3 GetScale() const;
	void SetScale(Vector3 scale);
	
	
private:
	Vector3 globalScale;
	GLFWwindow* main_window;
	unsigned int shaderProgram;

	ShaderSourceCode ParseShader(const std::string& filePath) const;
	static unsigned int InitShaders(const ShaderSourceCode& code);
	static unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};

#endif
