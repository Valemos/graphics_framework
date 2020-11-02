#include "Object3D.h"


#include "../ProgramInputHandler.h"
#include "../Renderer.h"
#include "Primitive.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void Object3D::LoadGLTransform(Renderer& renderer, const Vector3& position) const
{
	// calculate local space transform matrix
	glm::mat4 transform = glm::mat4(1.0f);
	transform = scale(transform, figure_scale);

	// world space transform
	transform = translate(transform, position.ToGlm());

	// camera transform
	const float window_aspect_ratio = ProgramInputHandler::window_size.x / ProgramInputHandler::window_size.y;
	auto& camera = renderer.get_camera();
	transform = camera.get_projection(window_aspect_ratio) * camera.get_view_matrix() * transform;

	static const auto transform_loc = glGetUniformLocation(renderer.get_shader_program(), "transform");
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(transform));
}

void Object3D::Draw(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);
	static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");

	LoadGLTransform(renderer, object_position_);
	
	LoadGLBuffers();

	// draw all primitives
	unsigned first_index_position = 0;
	glUniform4fv(color_loc, 1, value_ptr(surface_color));
	for (auto* primitive : primitives)
	{
		primitive->Draw((void*)first_index_position);
		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}

void Object3D::DrawWireframe(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);
	static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");

	LoadGLTransform(renderer, object_position_);
	LoadGLBuffers();

	glLineWidth(2.f);
	
	unsigned first_index_position = 0;
	glUniform4fv(color_loc, 1, value_ptr(edge_color));
	for (auto* primitive : primitives)
	{
		primitive->DrawBorder((void*)first_index_position);
		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}
