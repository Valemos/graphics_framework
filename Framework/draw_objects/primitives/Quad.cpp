#include "Quad.h"

#include <stdexcept>


#include "GL/glew.h"

Quad::Quad(const std::vector<unsigned int>& positions) : Primitive(positions)
{
	if (positions.size() % 4 != 0)
	{
		throw(std::invalid_argument("Not a set of quadrilaterals"));
	}
}

std::vector<unsigned> Quad::get_triangle_indices() const
{
	// for each 4 points of quad we create two triangles
	std::vector<unsigned int> triangles;
	triangles.reserve(get_triangle_indices_count());
	auto it = vertex_indices_.begin();
	while (it != vertex_indices_.end())
	{
		triangles.push_back(*it);
		triangles.push_back(*(it + 1));
		triangles.push_back(*(it + 2));
		triangles.push_back(*it);
		triangles.push_back(*(it + 2));
		triangles.push_back(*(it + 3));
		it += 4;
	}

	return triangles;
}

unsigned Quad::get_triangle_indices_count() const
{
	return vertex_indices_.size() / 2 * 3;
}

void Quad::Draw(const void* offset) const
{
	glDrawElements(GL_QUADS, vertex_indices_.size(), GL_UNSIGNED_INT, offset);
}
