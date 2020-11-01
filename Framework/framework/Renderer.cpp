#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <fstream>

Renderer::Renderer()
{
    main_window_ = nullptr;
    shader_program_ = -1; // will write maximum possible value for uint
}

GLFWwindow* Renderer::get_window() const
{
    return this->main_window_;
}

void Renderer::LoadShadersFromFile(const std::string& file_path)
{
	const auto program_code = ParseShader(file_path);
    shader_program_ = InitShaders(program_code);
}

int Renderer::get_shader_program() const
{
    return shader_program_;
}

Camera& Renderer::get_camera()
{
    return main_camera_;
}

int Renderer::InitGraphics(int width, int height)
{
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    main_window_ = glfwCreateWindow(width, height, "Figure", NULL, NULL);
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

    glViewport(0, 0, width, height);

    return 0;
}

ShaderSourceCode Renderer::ParseShader(const std::string& filePath) const
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filePath);

    std::string line;
    std::stringstream strStreams[2];
    ShaderType curType = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                curType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                curType = ShaderType::FRAGMENT;
            }
        }
        else if (curType != ShaderType::NONE)
        {
            strStreams[(int)curType] << line << std::endl;
        }
    }

    return { strStreams[0].str(), strStreams[1].str() };
}

unsigned int Renderer::CompileShader(unsigned int type, const std::string& sourceCode)
{
    unsigned int shaderId = glCreateShader(type);
    const char* src = sourceCode.c_str();
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    int result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(shaderId, length, &length, message);

        std::cout << "Failed to compile ";
        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

unsigned int Renderer::InitShaders(const ShaderSourceCode& code)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, code.Vertex);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, code.Fragment);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
