#include "Line.h"

#include <GL/glew.h>

std::vector<unsigned> Line::get_triangle_indices() const
{
	return vertex_indices_;
}

unsigned Line::get_triangle_indices_count() const
{
	return vertex_indices_.size();
}

void Line::Draw(const void* offset) const
{
	glDrawElements(GL_LINES, vertex_indices_.size(), GL_UNSIGNED_INT, offset);
}
