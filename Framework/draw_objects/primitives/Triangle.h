#ifndef GL_LAB1_TRIANGLE
#define GL_LAB1_TRIANGLE

#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Triangle(const std::vector<unsigned int>& positions);

	std::vector<unsigned> get_triangle_indices() const override;
	unsigned get_triangle_indices_count() const override;
	void Draw(const void* offset) const override;
};

#endif // !GL_LAB1_TRIANGLE