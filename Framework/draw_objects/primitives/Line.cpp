#include "Line.h"

#include <GL/glew.h>

std::vector<unsigned> Line::get_triangle_indices() const
{
	return indices_;
}

unsigned Line::get_triangle_indices_count() const
{
	return indices_.size();
}

void Line::Draw(const void* offset) const
{
	glDrawElements(GL_LINE_STRIP, indices_.size(), GL_UNSIGNED_INT, offset);
}
