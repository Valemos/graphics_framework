#include "Triangle.h"

#include <stdexcept>


#include "GL/glew.h"

Triangle::Triangle(const std::vector<unsigned int>& positions) : Primitive(positions)
{
	if (positions.size() % 3 != 0)
	{
		throw std::length_error("Length of vector is not correct");
	}
}

std::vector<unsigned> Triangle::get_triangle_indices() const
{
	return vertex_indices_;
}

unsigned Triangle::get_triangle_indices_count() const
{
	return vertex_indices_.size();
}

void Triangle::Draw(const void* offset) const
{
	glDrawElements(GL_TRIANGLES, vertex_indices_.size(), GL_UNSIGNED_INT, offset);
}
