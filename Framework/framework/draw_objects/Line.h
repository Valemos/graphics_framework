#pragma once

#include "Primitive.h"

class Line : public Primitive 
{
public:
	explicit Line(const std::vector<unsigned>& indices)
		: Primitive(indices)
	{
	}

	std::vector<unsigned> get_triangle_indices() const override;
	unsigned get_triangle_indices_count() const override;
	void Draw(const void* offset) const override;
};

