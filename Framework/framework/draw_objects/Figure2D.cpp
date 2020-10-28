#include "Figure2D.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Primitive.h"


Figure2D::Figure2D(): fill_color(0.f, 0.f, 0.f), border_color(0.f, 0.f, 0.f), figure_scale(1.f, 1.f, 1.f)
{
}

void Figure2D::set_fill_color(float r, float g, float b)
{
	fill_color = glm::vec3(r, g, b);
}

void Figure2D::set_border_color(float r, float g, float b)
{
	border_color = glm::vec3(r, g, b);
}

void Figure2D::set_scale(float x_scale, float y_scale, float z_scale)
{
	figure_scale = glm::vec3(x_scale, y_scale, z_scale);
}

void Figure2D::Draw(const Renderer& renderer, const Vector3& position)
{
	const unsigned int shader_program = renderer.GetShaderProgram();
	glUseProgram(shader_program);
	static const int transform_loc = glGetUniformLocation(shader_program, "transform");
	static const int color_loc = glGetUniformLocation(shader_program, "fillColor");

	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);
	transform = translate(transform, glm::vec3(position.x, position.y, position.z));
	transform = scale(transform, renderer.GetScaleForGL());
	transform = scale(transform, figure_scale);
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(transform));

	LoadGLBuffers();
	
	glLineWidth(2.f);
	unsigned first_index_position = 0;
	for (auto* primitive : primitives)
	{
		glUniform4fv(color_loc, 1, value_ptr(fill_color));
		primitive->Draw((void*)first_index_position);

		glUniform4fv(color_loc, 1, value_ptr(border_color));
		primitive->DrawBorder((void*)first_index_position);

		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}
