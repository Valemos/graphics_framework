#include "Grid2D.h"

#include "../draw_objects/Line.h"

Grid2D::Grid2D(std::vector<std::vector<Vector3>>& points_array)
{
	SetBorderColor(1.0, 0, 0);
	grid_array_height_ = points_array.size();
	grid_array_width_ = points_array[0].size();

	// create primitives and load them to GL buffers		
	std::vector<Vector3> vertices;
	std::vector<std::vector<unsigned>> vertex_indices;
	std::vector<Primitive*> primitives;
	vertices.reserve(points_array[0].size() * points_array.size());
	primitives.reserve(points_array[0].size() + points_array.size());

	// put all indices into one buffer and save their indices in grid
	unsigned cur_index = 0;
	vertex_indices.resize(points_array.size());
	for (unsigned y_i = 0; y_i < points_array.size(); ++y_i)
	{
		vertex_indices[y_i].resize(points_array[y_i].size(), 0);
		for (unsigned x_i = 0; x_i < points_array[y_i].size(); ++x_i)
		{
			vertex_indices[y_i][x_i] = cur_index++;
			vertices.emplace_back(points_array[y_i][x_i]);
		}
	}

	// create horizontal lines from indices
	for (unsigned row = 0; row < vertex_indices.size(); ++row)
	{
		primitives.emplace_back(new Line( std::vector<unsigned>(vertex_indices[row])));
	}

	// create vertical lines from indices
	for (unsigned x_i = 0; x_i < vertex_indices[0].size(); ++x_i)
	{
		auto* line_vertical_indices = new std::vector<unsigned>();
		line_vertical_indices->reserve(vertex_indices.size());
		
		for (int y_i = 0; y_i < vertex_indices[x_i].size(); ++y_i)
		{
			line_vertical_indices->emplace_back(vertex_indices[y_i][x_i]);
		}
		
		primitives.emplace_back(new Line(*line_vertical_indices));
	}
	
	InitBuffers(vertices, primitives);
}

unsigned Grid2D::GetHeight() const
{
	return grid_array_height_;
}

unsigned Grid2D::GetWidth() const
{
	return grid_array_width_;
}

Vector3 Grid2D::GetPoint(unsigned x, unsigned y)
{
	const unsigned vertex_buf_index = (y * grid_array_width_ + x) * 3;

	return {
		vertex_buffer_[vertex_buf_index],
		vertex_buffer_[vertex_buf_index + 1],
		vertex_buffer_[vertex_buf_index + 2]
	};
}

void Grid2D::ReplacePoint(unsigned x, unsigned y, Vector3& point_new)
{
	const unsigned vertex_buf_index = (y * grid_array_width_ + x) * 3;
	vertex_buffer_[vertex_buf_index] = point_new.x;
	vertex_buffer_[vertex_buf_index + 1] = point_new.y;
	vertex_buffer_[vertex_buf_index + 2] = point_new.z;
}
