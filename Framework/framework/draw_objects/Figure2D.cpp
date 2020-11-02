#include "Figure2D.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Primitive.h"


Figure2D::Figure2D(): fill_color_(0.f, 0.f, 0.f), border_color_(0.f, 0.f, 0.f), figure_scale_(1.f, 1.f, 1.f)
{
}

void Figure2D::set_fill_color(float r, float g, float b)
{
	fill_color_ = glm::vec3(r, g, b);
}

void Figure2D::set_border_color(float r, float g, float b)
{
	border_color_ = glm::vec3(r, g, b);
}

void Figure2D::set_scale(float x_scale, float y_scale, float z_scale)
{
	figure_scale_ = glm::vec3(x_scale, y_scale, z_scale);
}

void Figure2D::Draw(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);
	static const auto transform_loc = glGetUniformLocation(shader_program, "transform");
	static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");

	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);
	transform = translate(transform, glm::vec3(object_position_.x, object_position_.y, object_position_.z));
	transform = scale(transform, figure_scale_);
	transform = scale(transform, renderer.get_global_scale());
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(transform));

	LoadGLBuffers();
	
	glLineWidth(2.f);
	unsigned first_index_position = 0;
	for (auto* primitive : primitives)
	{
		glUniform4fv(color_loc, 1, value_ptr(fill_color_));
		primitive->Draw((void*)first_index_position);

		glUniform4fv(color_loc, 1, value_ptr(border_color_));
		primitive->DrawBorder((void*)first_index_position);

		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}
