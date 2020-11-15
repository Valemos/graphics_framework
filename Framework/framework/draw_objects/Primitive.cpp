#include "Primitive.h"
#include "GL/glew.h"

Primitive::Primitive(const std::vector<unsigned int>& indices)
{
	vertex_indices_ = indices;
}

Primitive::~Primitive()
{
	// TODO: this can cause some errors, be alert
	delete &vertex_indices_;
}

void Primitive::DrawBorder(const void* offset) const
{
	glDrawElements(GL_LINE_LOOP, vertex_indices_.size(), GL_UNSIGNED_INT, offset);
}

const std::vector<unsigned>& Primitive::get_indices() const
{
	return vertex_indices_;
}

void Primitive::set_indices(const std::vector<unsigned>& indices_new)
{
	vertex_indices_.clear();
	vertex_indices_ = indices_new;
}
