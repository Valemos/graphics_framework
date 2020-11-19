#include "Figure2D.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Primitive.h"


void Figure2D::SetFillColor(float r, float g, float b)
{
	fill_color_ = glm::vec3(r, g, b);
}

void Figure2D::SetBorderColor(float r, float g, float b)
{
	border_color_ = glm::vec3(r, g, b);
}

void Figure2D::SetBorderWidth(float w)
{
	border_width_ = w;
}

void Figure2D::SetScale(float x_scale, float y_scale, float z_scale)
{
	figure_scale_ = glm::vec3(x_scale, y_scale, z_scale);
}

void Figure2D::LoadGLTransform(Renderer& renderer, const Vector3& position) const
{
	const unsigned int shader_program = renderer.get_shader_program();
	static const auto transform_loc = glGetUniformLocation(shader_program, "transform");

	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);
	transform = translate(transform, position.Scale(Vector3::FromGlm(renderer.GetGlobalScale())).ToGlm());
	transform = scale(transform, figure_scale_);
	transform = scale(transform, renderer.GetGlobalScale());
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(transform));
}

void Figure2D::Draw(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);
	
	static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");

	LoadGLTransform(renderer, object_position_);
	LoadGLBuffers();

	glUniform4fv(color_loc, 1, value_ptr(fill_color_));
	unsigned first_index_position = 0;
	for (auto* primitive : primitives_)
	{
		primitive->Draw((void*)first_index_position);
		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}

void Figure2D::DrawWireframe(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);
	static const auto transform_loc = glGetUniformLocation(shader_program, "transform");
	static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");

	LoadGLTransform(renderer, object_position_);
	LoadGLBuffers();

	glLineWidth(border_width_);
	glUniform4fv(color_loc, 1, value_ptr(border_color_));
	unsigned first_index_position = 0;
	for (auto* primitive : primitives_)
	{
		primitive->DrawBorder((void*)first_index_position);
		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}
