#include "Figure.h"

#include <glm/ext/matrix_transform.hpp>


Figure::Figure(): fill_color(0.f, 0.f, 0.f), border_color(0.f, 0.f, 0.f), figure_scale(1.f, 1.f, 1.f)
{
}

void Figure::set_fill_color(float r, float g, float b)
{
	fill_color = glm::vec3(r, g, b);
}

void Figure::set_border_color(float r, float g, float b)
{
	border_color = glm::vec3(r, g, b);
}

void Figure::set_scale(float x_scale, float y_scale, float z_scale)
{
	figure_scale = glm::vec3(x_scale, y_scale, z_scale);
}

void Figure::set_vertices(const std::vector<Vector3>& vertices)
{
	
}

void Figure::set_primitives(const std::vector<Primitive*>& new_primitives)
{
}

void Figure::UpdateGLBuffer()
{
}

void Figure::Draw(const Renderer& renderer, const Vector3& position)
{
	const unsigned int shaderProgram = renderer.GetShaderProgram();
	glUseProgram(shaderProgram);


	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);

	transform = translate(transform, glm::vec3(position.x, position.y, position.z));
	transform = scale(transform, renderer.GetScaleForGL());
	
	// get variable locations from shader
	static const int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	static const int colorLoc = glGetUniformLocation(shaderProgram, "fillColor");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4fv(colorLoc, 1, value_ptr(color));
}
