#ifndef GL_LAB1_RENDERER
#define GL_LAB1_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <glm/vec3.hpp>

#include "Vector3.h"
#include "draw_objects/Camera.h"

struct ShaderSourceCode {
        std::string Vertex;
        std::string Fragment;
};

class Renderer
{
public:
	Renderer();

    void LoadShadersFromFile(const std::string& file_path);
	int get_shader_program() const;
	Camera& get_camera();
	void SetGlobalScale(glm::vec3 global_scale);
	glm::vec3 GetGlobalScale() const;

private:
	
	Camera main_camera_ = Camera({0, 0, 0}, {0, 0, 0});
	
	unsigned int shader_program_;
	glm::vec3 global_scale_ {1, 1, 1};
	
	ShaderSourceCode ParseShader(const std::string& filePath) const;
	static unsigned int InitShaders(const ShaderSourceCode& code);
	static unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};

#endif
