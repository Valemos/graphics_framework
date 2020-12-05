#include "Object3D.h"


#include "../ProgramInputHandler.h"
#include "../Renderer.h"
#include "draw_objects/primitives/Primitive.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void Object3D::LoadGlLightSources(Renderer &renderer) const {

    // calculate light position
    static const auto light_pos_loc = glGetUniformLocation(renderer.get_shader_program(), "lightPos");
    glUniform3fv(light_pos_loc, 1, value_ptr(renderer.light_source.position.ToGlm()));

    static const auto light_color_loc = glGetUniformLocation(renderer.get_shader_program(), "lightColor");
    glUniform3fv(light_color_loc, 1, value_ptr(renderer.light_source.color.ToGlm()));

    // load camera position
    static const auto view_pos_loc = glGetUniformLocation(renderer.get_shader_program(), "viewPos");
    glUniform3fv(view_pos_loc, 1, value_ptr(renderer.get_camera().get_position().ToGlm()));
}

void Object3D::LoadGlTransform(Renderer& renderer, const Vector3& position) const
{
	// calculate model transformation matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = scale(model, figure_scale);
    model = translate(model, position.ToGlm());

    LoadGlLightSources(renderer);

    // camera transform
	const float window_aspect_ratio = ProgramInputHandler::window_size.x / ProgramInputHandler::window_size.y;
	auto& camera = renderer.get_camera();
    glm::mat4 view_transform = camera.GetProjection(window_aspect_ratio) * camera.get_view_matrix();

	static const auto view_transform_loc = glGetUniformLocation(renderer.get_shader_program(), "view");
	static const auto model_transform_loc = glGetUniformLocation(renderer.get_shader_program(), "model");

	glUniformMatrix4fv(view_transform_loc, 1, GL_FALSE, value_ptr(view_transform));
	glUniformMatrix4fv(model_transform_loc, 1, GL_FALSE, value_ptr(model));
}

void Object3D::LoadGlObjectProperties(Renderer &renderer) const {
    static const auto color_loc = glGetUniformLocation(renderer.get_shader_program(), "fillColor");
    glUniform4fv(color_loc, 1, value_ptr(primary_color));
}

void Object3D::Draw(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);

    LoadGlTransform(renderer, object_position_);
    LoadGlObjectProperties(renderer);
    LoadGlBuffers();

    // Draw all triangles with single call
	glDrawArrays(GL_TRIANGLES, 0, object_buffer_.size() / one_object_floats_);
}

void Object3D::DrawWireframe(Renderer& renderer)
{
	const unsigned int shader_program = renderer.get_shader_program();
	glUseProgram(shader_program);

    LoadGlTransform(renderer, object_position_);
    LoadGlBuffers();


    static const auto color_loc = glGetUniformLocation(shader_program, "fillColor");
    glUniform4fv(color_loc, 1, value_ptr(edge_color));

    glLineWidth(5.f);
    unsigned first_pos = 0;
    for (auto* tri : triangles_)
	{
	    glDrawArrays(GL_LINE_LOOP, first_pos++, 3);
    }
}

void Object3D::InitGlBuffers() {

    // we must create single buffer for all primitives using vertices and normals
    glGenVertexArrays(1, &VAO_id);
    glBindVertexArray(VAO_id);

    //bind all additional buffers
    glGenBuffers(1, &object_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, object_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, object_buffer_.size() * sizeof(float), 0, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    one_object_floats_ = 6;
}

void Object3D::LoadGlBuffers() {
    glBindVertexArray(VAO_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, object_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, object_buffer_.size() * sizeof(float), object_buffer_.data(), GL_STATIC_DRAW);
}

void Object3D::PackVerticesPrimitives(const std::vector<Vector3> &vertices, const std::vector<Primitive*> &primitives) {
    /// creates single buffer for all vertex data and loads it into it
    /// can free only normals buffer, because triangles and vertices can be used to draw wireframe

    SetPrimitives(primitives);

    auto& triangles = GetTriangles(primitives);
    auto& normals = GetNormals(vertices, triangles);

    object_buffer_.clear();
    object_buffer_.reserve(normals.size() * sizeof(float) * 6);

    unsigned normal_index = 0;
    for (auto* triangle : triangles) {
        for (auto v_index : triangle->get_indices()){
            object_buffer_.emplace_back(vertices[v_index].x);
            object_buffer_.emplace_back(vertices[v_index].y);
            object_buffer_.emplace_back(vertices[v_index].z);

            object_buffer_.emplace_back(normals[normal_index].x);
            object_buffer_.emplace_back(normals[normal_index].y);
            object_buffer_.emplace_back(normals[normal_index].z);
            normal_index++;
        }
    }

    InitGlBuffers();
}
