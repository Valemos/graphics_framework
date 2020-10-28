#include "Drawable.h"

#include "GL/glew.h"
#include "Primitive.h"
#include "Vector3.h"

Drawable::~Drawable()
{
	for(auto* prim : primitives)
	{
		delete prim;
	}
	vertex_buffer_.clear();
	index_buffer_.clear();
}

void Drawable::InitBuffers(const std::vector<Vector3>& vertices, const std::vector<Primitive*>& primitives)
{
	set_vertices(vertices);
	set_primitives(primitives);
	InitGLBuffer();
}

void Drawable::set_vertices(const std::vector<Vector3>& vertices)
{
	vertex_buffer_.clear();
	vertex_buffer_.reserve(vertices.size() * 3);
	for (const Vector3& vertex : vertices)
	{
		vertex_buffer_.push_back(vertex.x);
		vertex_buffer_.push_back(vertex.y);
		vertex_buffer_.push_back(vertex.z);
	}
}

void Drawable::set_primitives(const std::vector<Primitive*>& new_primitives)
{
	for (auto* prim : primitives)
	{
		delete prim;
	}
	primitives.clear();
	primitives = new_primitives;

	unsigned indices_count = 0;
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

void Drawable::InitGLBuffer()
{
	glGenVertexArrays(1, &vertex_array_object_id_);
	glBindVertexArray(vertex_array_object_id_);

	glGenBuffers(1, &index_buffer_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.size() * sizeof(unsigned), 0, GL_STATIC_DRAW);

	glGenBuffers(1, &vertex_buffer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.size() * sizeof(float), 0, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Drawable::LoadGLBuffers()
{
	glBindVertexArray(vertex_array_object_id_);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_.size() * sizeof(unsigned), index_buffer_.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id_);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.size() * sizeof(float), vertex_buffer_.data(), GL_STATIC_DRAW);
}
