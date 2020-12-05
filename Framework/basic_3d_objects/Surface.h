#pragma once

#include "../draw_objects/Object3D.h"
#include "draw_objects/primitives/Triangle.h"
#include "draw_objects/primitives/Quad.h"

class Surface : public Object3D
{
	const float grid_step = 0.1;
	std::vector<std::vector<float>>& grid_values_;

public:
	
	Surface(std::vector<std::vector<float>>& grid_values, const glm::vec3& surface_color, const glm::vec3& edge_color, const glm::vec3& figure_scale = {1, 1, 1})
		: Object3D(surface_color, edge_color, figure_scale), grid_values_(grid_values)
	{
	}

    void CreateObject() override {
        std::vector<Vector3> vertices;
        std::vector<std::vector<unsigned>> vertex_indices;
        std::vector<Primitive*> primitives;
        vertices.reserve(grid_values_[0].size() * grid_values_.size());
        primitives.reserve((grid_values_[0].size() - 1) * (grid_values_.size() - 1));

        // put all indices into one buffer and save their indices in grid
        unsigned cur_index = 0;
        vertex_indices.resize(grid_values_.size());
        for (unsigned y_i = 0; y_i < grid_values_.size(); ++y_i)
        {
            vertex_indices[y_i].resize(grid_values_[y_i].size(), 0);
            for (unsigned x_i = 0; x_i < grid_values_[y_i].size(); ++x_i)
            {
                vertex_indices[y_i][x_i] = cur_index++;
                vertices.emplace_back(Vector3{ x_i * grid_step, grid_values_[y_i][x_i], y_i * grid_step });
            }
        }

        // create Quads
        for (unsigned y_i = 1; y_i < vertex_indices.size(); ++y_i)
        {
            for (unsigned x_i = 1; x_i < vertex_indices[y_i].size(); ++x_i)
            {
                primitives.emplace_back(new Triangle(
                        Quad({
                                     vertex_indices[y_i - 1][x_i - 1],
                                     vertex_indices[y_i][x_i - 1],
                                     vertex_indices[y_i][x_i],
                                     vertex_indices[y_i - 1][x_i]
                             }).get_triangle_indices()));
            }
        }

        PackVerticesPrimitives(vertices, primitives);
    }
};
