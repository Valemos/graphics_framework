#include "Object3D.h"


#include "../ProgramInputHandler.h"
#include "../Renderer.h"
#include "draw_objects/primitives/Primitive.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void Object3D::LoadGlTransform(Renderer& renderer, const Vector3& position) const
{
	// calculate local space transform matrix
	glm::mat4 transform = glm::mat4(1.0f);
	transform = scale(transform, figure_scale);

	// world space transform
	transform = translate(transform, position.ToGlm());

	// camera transform
	const float window_aspect_ratio = ProgramInputHandler::window_size.x / ProgramInputHandler::window_size.y;
	auto& camera = renderer.get_camera();
	transform = camera.GetProjection(window_aspect_ratio) * camera.get_view_matrix() * transform;

	static const auto transform_loc = glGetUniformLocation(renderer.get_shader_program(), "transform");
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(transform));
}

void Object3D::Draw(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);
	static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");

    LoadGlTransform(renderer, object_position_);
	LoadGlBuffers();

	// Draw all primitives
	unsigned first_index_position = 0;
	glUniform4fv(color_loc, 1, value_ptr(primary_color));
	for (auto* primitive : primitives_)
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

    LoadGlTransform(renderer, object_position_);
	LoadGlBuffers();

	glLineWidth(2.f);
	
	unsigned first_index_position = 0;
	glUniform4fv(color_loc, 1, value_ptr(edge_color));
	for (auto* primitive : primitives_)
	{
		primitive->DrawBorder((void*)first_index_position);
		first_index_position += primitive->get_indices().size() * sizeof(GLuint);
	}
}

void Object3D::InitGlBuffers() {
    glGenVertexArrays(1, &vertex_array_object_id_);
    glBindVertexArray(vertex_array_object_id_);

    glGenBuffers(1, &index_buffer_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.size() * sizeof(unsigned), 0, GL_STATIC_DRAW);

    //bind all additional buffers
    glGenBuffers(1, &vertex_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, (vertex_buffer_.size() + normals_buffer_.size()) * sizeof(float), 0, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) (vertex_buffer_.size() * sizeof(float)));
}

void Object3D::LoadGlBuffers() {
    glBindVertexArray(vertex_array_object_id_);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.size() * sizeof(unsigned), index_buffer_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);

    // vertices data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_buffer_.size() * sizeof(float), vertex_buffer_.data());
    // bind normals data to the end of main buffer
//    glBufferSubData(GL_ARRAY_BUFFER, vertex_buffer_.size() * sizeof(float), normals_buffer_.size() * sizeof(float), normals_buffer_.data());

}
