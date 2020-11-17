#pragma once

#include "Program.h"
#include "draw_objects/Figure2D.h"
#include "Vector3.h"


class SpaceMetricGrid : public Program
{
	Figure2D* figure_;
	
public:
	explicit SpaceMetricGrid(float fps) : Program(fps), figure_(nullptr){}

	Vector3 PolarToCartesian(Vector3& point) const;
	Vector3 CustomTransform(Vector3& point) const;
	
	std::vector<std::vector<Vector3>> CalculateGridLines(float axis1_min, float axis1_max, float axis2_min, float axis2_max, float grid_step) const;
	int Init() override;
	int Step() override;
};
