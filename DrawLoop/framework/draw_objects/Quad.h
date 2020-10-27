#ifndef GL_LAB1_KB_QUAD
#define GL_LAB1_KB_QUAD

#include "Primitive.h"
#include <string>

class Quad : public Primitive
{
public:
	Quad(const std::vector<unsigned int>& positions);

	std::vector<unsigned> get_triangle_indices() const override;
	unsigned get_triangle_indices_count() const override;
	void Draw(const void* offset) const override;
};

#endif