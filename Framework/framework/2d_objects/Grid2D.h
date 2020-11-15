#pragma once

#include "../draw_objects/Figure2D.h"

class Grid2D : public Figure2D
{
	unsigned grid_array_width_;
	unsigned grid_array_height_;
	
public:
	Grid2D(std::vector<std::vector<Vector3>>& points_array);

	unsigned GetHeight() const;
	unsigned GetWidth() const;
	Vector3 GetPoint(unsigned x, unsigned y);
	void ReplacePoint(unsigned x, unsigned y, Vector3& point_new);
};
