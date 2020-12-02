#include "TriangleFan.h"

#include "GL/glew.h"

void TriangleFan::Draw(const void* offset) const
{
	glDrawElements(GL_POLYGON, vertex_indices_.size(), GL_UNSIGNED_INT, offset);
}

std::vector<unsigned> TriangleFan::get_triangle_indices() const
{
	std::vector<unsigned> triangles;
	triangles.reserve(vertex_indices_.size() - 2);
	
	unsigned first = vertex_indices_[0];
	for (int i = 1; i < vertex_indices_.size(); ++i)
	{
		triangles.emplace_back(first);
		triangles.emplace_back(vertex_indices_[i]);
		triangles.emplace_back(vertex_indices_[i + 1]);
	}
	return triangles;
}

unsigned TriangleFan::get_triangle_indices_count() const
{
	return (vertex_indices_.size() - 2) * 3;
}

void TriangleFan::DrawBorder(const void* offset) const
{
	glDrawElements(GL_LINE_LOOP, vertex_indices_.size(), GL_UNSIGNED_INT, offset);
}
