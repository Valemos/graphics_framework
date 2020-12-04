#include "Grid2D.h"

#include "draw_objects/primitives/Line.h"

Grid2D::Grid2D(std::vector<std::vector<Vector3>>& points_array, int intermediate_count)
{
	SetBorderColor(1.0, 0, 0);

	const unsigned total_intermediate_height_ = (points_array.size() - 1) * intermediate_count;
	const unsigned total_intermediate_width_ = (points_array[0].size() - 1) * intermediate_count;
	const unsigned grid_size_x = points_array[0].size();
	const unsigned grid_size_y = points_array.size();
	
	grid_array_height_ = points_array.size() + total_intermediate_height_;
	grid_array_width_ = points_array[0].size() + total_intermediate_width_;

	// create primitives and load them to GL buffers		
	std::vector<Vector3> vertices;
	std::vector<std::vector<unsigned>> shared_indices_array;
	std::vector<Primitive*> primitives;
	vertices.reserve(grid_array_width_ * grid_array_height_);
	primitives.reserve((grid_size_x - 1) * (grid_size_y - 1));

	unsigned cur_index = 0;
	
	// horizontal lines
	shared_indices_array.resize(grid_size_y);
	for (int y_i = 0; y_i < grid_size_y; ++y_i)
	{
		shared_indices_array[y_i].resize(grid_size_x);
		for (int x_i = 0; x_i < grid_size_x - 1; ++x_i)
		{
			auto line_indices = std::vector<unsigned>();
			line_indices.reserve(intermediate_count + 2);
			
			// first point
			line_indices.emplace_back(cur_index);
			shared_indices_array[y_i][x_i] = cur_index++;
			vertices.emplace_back(points_array[y_i][x_i]);

			// intermediate points
			const Vector3 step = (points_array[y_i][x_i + 1] - points_array[y_i][x_i]) / (intermediate_count + 1);
			Vector3 current = points_array[y_i][x_i];

			for (int i = 0; i < intermediate_count; ++i)
			{
				current += step;
				line_indices.emplace_back(cur_index++);
				vertices.emplace_back(current);
			}

			// this point will be added to buffer on the next loop
			// and will be the beginning of next line
			line_indices.emplace_back(cur_index);
			primitives.emplace_back(new Line(line_indices));
		}

		// add the last point
		shared_indices_array[y_i][grid_size_x - 1] = cur_index++;
		vertices.emplace_back(points_array[y_i][grid_size_x - 1]);
	}


	// vertical lines
	for (int x_i = 0; x_i < grid_size_x; ++x_i)	
	{
		for (int y_i = 0; y_i < grid_size_y - 1; ++y_i)
		{
			auto line_indices = std::vector<unsigned>();
			line_indices.reserve(intermediate_count + 2);

			// first point
			line_indices.emplace_back(shared_indices_array[y_i][x_i]);

			// intermediate points
			const Vector3 step = (points_array[y_i][x_i] - points_array[y_i + 1][x_i]) / (intermediate_count + 1);
			Vector3 current = points_array[y_i][x_i];

			for (int i = 0; i < intermediate_count; ++i)
			{
				current -= step;
				line_indices.emplace_back(cur_index++);
				vertices.emplace_back(current);
			}

			line_indices.emplace_back(shared_indices_array[y_i + 1][x_i]);
			primitives.emplace_back(new Line(line_indices));
		}
	}

    SetVertexBuffer(vertices);
	SetPrimitives(primitives);
	InitGlBuffers();
}


unsigned Grid2D::GetHeight() const
{
	return grid_array_height_;
}

unsigned Grid2D::GetWidth() const
{
	return grid_array_width_;
}

std::vector<float>& Grid2D::GetPoints()
{
	return vertex_buffer_;
}

void Grid2D::UpdatePoint(Vector3& point, unsigned start_index)
{
	vertex_buffer_[start_index] = point.x;
	vertex_buffer_[start_index + 1] = point.y;
	vertex_buffer_[start_index + 2] = point.z;
}

void Grid2D::UpdatePoints(const std::vector<Vector3>& points_new)
{
	if (points_new.size() * 3 > vertex_buffer_.size())
	{
		throw std::exception("sizes does not fit");
	}
	
	auto current_index = 0;
	for (const auto& point : points_new)
	{
		vertex_buffer_[current_index++] = point.x;
		vertex_buffer_[current_index++] = point.y;
		vertex_buffer_[current_index++] = point.z;
	}
}
