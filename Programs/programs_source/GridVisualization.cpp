#include "GridVisualization.h"

double GridVisualization::s_last_space_press = 0;
bool GridVisualization::s_space_pressed = false;

int GridVisualization::HandleSpace(void*)
{
	if (!s_space_pressed && glfwGetTime() - s_last_space_press > 0.2)
	{
		s_space_pressed = true;
	}
	return 0;
}

int GridVisualization::Init()
{
    auto handlers = std::vector<ButtonHandler>{
        ButtonHandler(Key::Space, HandleSpace)
    };
    ProgramInputHandler::AddButtonHandlers(handlers);

    points_grid_ = std::vector< std::vector<Vector3> >(grid_height_count_);

    const float x_start = grid_start_.x;
    const float y_start = grid_start_.y + grid_height_count_ * grid_step_.y;
    const float x_step = grid_step_.x;
    const float y_step = -grid_step_.y;

    for (int y = 0; y < grid_height_count_; ++y)
    {
        points_grid_[y] = std::vector<Vector3>(grid_width_count_);
        for (int x = 0; x < grid_width_count_; ++x)
        {
            points_grid_[y][x] = {
                x * x_step + x_start,
                y * y_step + y_start,
            };
        }
    }

    ProgramInputHandler::SetClearColor(66, 135, 245);
    main_grid_ = new Grid2D(points_grid_, intermediate_points_);
    main_grid_->SetScale(1, 1);
    main_grid_->SetBorderColor(0, 0, 0);
    main_grid_->SetBorderWidth(0.2);
    main_grid_->Position() = { 0, 0 };

    return 0;
}

int GridVisualization::Step()
{
    if (s_space_pressed)
	{
		if (!attraction_targets_.empty())
		{
		    attraction_targets_.pop_back();
		}
		s_space_pressed = false;
		s_last_space_press = glfwGetTime();
    }

    if (ProgramInputHandler::clicked_position_ != nullptr)
    {
        auto* result_coordinate = ProgramInputHandler::clicked_position_;
        result_coordinate->y = -result_coordinate->y;
        attraction_targets_.emplace_back(*result_coordinate);

        delete ProgramInputHandler::clicked_position_;
        ProgramInputHandler::clicked_position_ = nullptr;
    }

    if (!attraction_targets_.empty())
    {
        UpdateGridPoints(attraction_speed_);
    }

    ProgramInputHandler::ClearScreen();
    main_grid_->Draw(ProgramInputHandler::renderer_);
    return 0;
}

Vector3& GridVisualization::ShiftTowardsPoint(Vector3& point, Vector3& target, float coefficient, float accuracy) const
{
    if (abs(point.x - target.x) < accuracy &&
        abs(point.y - target.y) < accuracy)
    {
        return point;
    }

    const float distance_sqr = point.DistanceSquared(target);
    const Vector3 direction = point.Direction(target, distance_sqr);
    const Vector3 shift = direction * -coefficient / distance_sqr;
    point += shift;

    if (shift.LengthSqr() - distance_sqr > accuracy)
    {
        return target;
    }
    return point;
}

void GridVisualization::UpdateGridPoints(float coefficient)
{
    auto points = main_grid_->GetPoints();
	for (int i = 0; i < points.size(); i += 3)
	{
        Vector3 point = { points[i], points[i + 1], points[i + 2] };
        for (auto target : attraction_targets_)
        {
            point = ShiftTowardsPoint(point, target, coefficient);
		}
        main_grid_->UpdatePoint(point, i);
	}
}
