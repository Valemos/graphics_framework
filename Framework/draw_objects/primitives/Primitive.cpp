#include "Primitive.h"
#include "GL/glew.h"

Primitive::Primitive(const std::vector<unsigned int>& indices)
{
    indices_ = indices;
}

void Primitive::DrawBorder(const void* offset) const
{
	glDrawElements(GL_LINE_LOOP, indices_.size(), GL_UNSIGNED_INT, offset);
}

const std::vector<unsigned>& Primitive::get_indices() const
{
	return indices_;
}

void Primitive::set_indices(const std::vector<unsigned>& indices_new)
{
	indices_.clear();
    indices_ = indices_new;
}
