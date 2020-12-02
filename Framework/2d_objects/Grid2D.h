#pragma once

#include "../draw_objects/Figure2D.h"

class Grid2D : public Figure2D
{
	unsigned grid_array_width_;
	unsigned grid_array_height_;
	
public:
	Grid2D(std::vector<std::vector<Vector3>>& points_array, int intermediate_count = 0);

	unsigned GetHeight() const;
	unsigned GetWidth() const;
	std::vector<float>& GetPoints();
	void UpdatePoint(Vector3& point, unsigned start_index);
	void UpdatePoints(const std::vector<Vector3>& points_new);
};
