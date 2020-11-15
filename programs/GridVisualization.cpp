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

    glClearColor(66 / 255.f, 135 / 255.f, 245 / 255.f, 1.0);
    main_grid_ = new Grid2D(points_grid_);
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

    if (ProgramInputHandler::clicked_position != nullptr)
    {
        auto* result_coordinate = ProgramInputHandler::clicked_position;
        result_coordinate->y = -result_coordinate->y;
        attraction_targets_.emplace_back(*result_coordinate);

        delete ProgramInputHandler::clicked_position;
        ProgramInputHandler::clicked_position = nullptr;
    }

    if (!attraction_targets_.empty())
    {
        UpdateGridPoints(attraction_speed_);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    main_grid_->Draw(ProgramInputHandler::renderer);
    return 0;
}

Vector3& GridVisualization::ShiftTowardsPoint(Vector3& point, Vector3& target, float koeficient, float accuracy) const
{
    if (abs(point.x - target.x) < accuracy &&
        abs(point.y - target.y) < accuracy)
    {
        return point;
    }

    const float distance_sqr = point.DistanceSquared(target);
    const Vector3 direction = point.Direction(target, distance_sqr);
    const Vector3 shift = direction * -koeficient / distance_sqr;
    point += shift;

    if (shift.LengthSqr() - distance_sqr > accuracy)
    {
        return target;
    }
    return point;
}

void GridVisualization::UpdateGridPoints(float coefficient)
{
	const auto grid_height = main_grid_->GetHeight();
	const auto grid_width = main_grid_->GetWidth();

	for (auto y = 0; y < grid_height; ++y)
	{
		for (auto x = 0; x < grid_width; ++x)
		{
			for (auto target : attraction_targets_)
			{
				auto point = main_grid_->GetPoint(x, y);
				point = ShiftTowardsPoint(point, target, coefficient);
				main_grid_->ReplacePoint(x, y, point);
			}
		}
	}
}
