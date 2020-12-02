#pragma once

#include "Program.h"
#include "2d_objects/Grid2D.h"
#include "draw_objects/primitives/Triangle.h"
#include "Vector3.h"


class GridVisualization :
    public Program
{
    const float attraction_speed_ = 0.1 / 60;
    std::vector<Vector3> attraction_targets_;
	
    Vector3 grid_start_;
    Vector3 grid_step_;
    int grid_width_count_;
    int grid_height_count_;
    int intermediate_points_;
    std::vector<std::vector<Vector3>> points_grid_;

    Grid2D* main_grid_ = nullptr;


    // handle space press
    static double s_last_space_press;
    static bool s_space_pressed;
	
public:
    GridVisualization(Vector3 grid_start, Vector3 grid_step, int width_count, int height_count, int intermediate_points) : Program(60.f), grid_start_(grid_start), grid_step_(grid_step), grid_width_count_(width_count), grid_height_count_(height_count), intermediate_points_(intermediate_points)
    {
    }

    static int HandleSpace(Program*);
	
    // Inherited via Program
    int Init() override;
    int Step() override;

    Vector3& ShiftTowardsPoint(Vector3& point, Vector3& target, float coefficient, float accuracy = 0.00001) const;
    void UpdateGridPoints(float coefficient);
};
