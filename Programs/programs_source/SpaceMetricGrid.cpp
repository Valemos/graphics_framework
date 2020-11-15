#include "SpaceMetricGrid.h"

#include "ProgramInputHandler.h"
#include "draw_objects/Line.h"
#include <math.h>


#define PI 3.1415926535

Vector3 SpaceMetricGrid::PolarToCartesian(Vector3& point) const
{
	return {point.x * cos(point.y), point.x * sin(point.y)};
}

std::vector<std::vector<Vector3>> SpaceMetricGrid::CalculateGridLines(float axis1_min, float axis1_max, float axis2_min, float axis2_max, float grid_step) const
{
	auto lines = std::vector<std::vector<Vector3>>();
	lines.reserve(axis1_min + axis1_max);

	const int lines_axis1 = (int) ceil((axis2_max - axis2_min) / grid_step);
	const int lines_axis2 = lines_axis1;
	const float angle_step = 2*PI / lines_axis2;
	
	// lines along axis 1
	Vector3 cur_point{axis1_min, axis2_min};
	for (int i = 0; i < lines_axis1; ++i)
	{
		auto new_line = std::vector<Vector3>();
		new_line.reserve(lines_axis2);

		// generate points with this fixed value of axis 2
		do
		{
			new_line.emplace_back(PolarToCartesian(cur_point));
			cur_point.x += grid_step;
		}
		while (cur_point.x < axis1_max);

		lines.emplace_back(new_line);
		cur_point.y += angle_step;
		cur_point.x = axis1_min;
	}
	
	// lines along axis 2
	cur_point = {axis1_min, axis2_min};
	for (int i = 0; i < lines_axis2; ++i)
	{
		auto new_line = std::vector<Vector3>();
		new_line.reserve(lines_axis1);

		// generate points with this fixed value of axis 2
		do
		{
			new_line.emplace_back(PolarToCartesian(cur_point));
			cur_point.y += angle_step;
		}
		while (cur_point.y < axis2_max);

		lines.emplace_back(new_line);
		cur_point.x += grid_step;
		cur_point.y = axis2_min;
	}
	
	return lines;
}

int SpaceMetricGrid::Init()
{
	figure_ = new Figure2D();

	// calculate lines on grid along axis
	auto lines = CalculateGridLines(0.01, 2, 0, 2*PI, 0.1);

	std::vector<Vector3> vertices;
	std::vector<Primitive*> primitives;
	vertices.reserve(lines[0].size() * lines.size());
	primitives.reserve(lines.size());
	
	unsigned index = 0;
	for (const auto& line : lines)
	{
		std::vector<unsigned> indices;
		indices.reserve(line.size());
		for (auto point : line)
		{
			vertices.emplace_back(point);
			indices.emplace_back(index++);
		}
		primitives.emplace_back(new Line(indices));
	}

	figure_->InitBuffers(vertices, primitives);
	figure_->Position() = Vector3{ 0, 0 };
	figure_->SetBorderColor(0, 1, 0);
	figure_->SetBorderWidth(1);
	
	ProgramInputHandler::SetClearColor(0, 66, 255);
	return 0;
}

int SpaceMetricGrid::Step()
{
	ProgramInputHandler::ClearScreen();
	figure_->Draw(ProgramInputHandler::renderer);
	return 0;
}
