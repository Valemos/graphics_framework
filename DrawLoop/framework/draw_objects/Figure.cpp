#include "Figure.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
	vertex_buffer_.clear();
	vertex_buffer_.reserve(vertices.size() * 3);
	for (auto vertex : vertices)
	{
		vertex_buffer_.push_back(vertex.x);
		vertex_buffer_.push_back(vertex.y);
		vertex_buffer_.push_back(vertex.z);
	}
}

void Figure::set_primitives(const std::vector<Primitive*>& new_primitives)
{
	primitives = new_primitives;
	
	unsigned int indices_count = 0;
	for (auto* prim : primitives)
	{
		indices_count += prim->get_indices().size();
	}

	index_buffer_.clear();
	index_buffer_.reserve(indices_count);

	for (auto* prim : primitives)
	{
		auto indices = prim->get_indices();
		index_buffer_.insert(index_buffer_.end(), indices.begin(), indices.end());
	}
}

void Figure::UpdateGLBuffer()
{
	// create buffers
	glGenVertexArrays(1, &vertex_array_object_id_);
	glBindVertexArray(vertex_array_object_id_);

	glGenBuffers(1, &vertex_buffer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.size(), vertex_buffer_.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &index_buffer_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.size(), index_buffer_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Figure::Draw(const Renderer& renderer, const Vector3& position)
{
	const unsigned int shaderProgram = renderer.GetShaderProgram();
	glUseProgram(shaderProgram);

	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);

	transform = translate(transform, glm::vec3(position.x, position.y, position.z));
	transform = scale(transform, renderer.GetScaleForGL());
	transform = scale(transform, figure_scale);
	
	// get variable locations from shader
	static const int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	static const int colorLoc = glGetUniformLocation(shaderProgram, "fillColor");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));


	glBindVertexArray(vertex_array_object_id_);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.size(), vertex_buffer_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.size(), index_buffer_.data(), GL_STATIC_DRAW);

	
	int buffer_offset = 0;
	for (auto* primitive : primitives)
	{
		glUniform4fv(colorLoc, 1, glm::value_ptr(fill_color));
		primitive->Draw((void*)buffer_offset);

		glUniform4fv(colorLoc, 1, glm::value_ptr(border_color));
		primitive->DrawBorder((void*)buffer_offset);

		buffer_offset += primitive->get_indices().size();
	}
}
