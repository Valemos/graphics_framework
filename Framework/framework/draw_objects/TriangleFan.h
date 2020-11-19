#pragma once

#include "draw_objects/Primitive.h"

class TriangleFan : public Primitive
{
public:
	explicit TriangleFan(const std::vector<unsigned>& indices)
		: Primitive(indices)
	{
	}

	void Draw(const void* offset) const override;
	std::vector<unsigned> get_triangle_indices() const override;
	unsigned get_triangle_indices_count() const override;
	void DrawBorder(const void* offset) const override;
};

