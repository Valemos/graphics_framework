
#include "ProgramInputHandler.h"

#include "programs_source/ProgramMultipleObjects.h"
#include "programs_source/GridVisualization.h"
#include "programs_source/SpaceMetricGrid.h"

const char* shader_path = "D:/coding/c_c++/GraphicalFramework/Framework/framework/shaders/main_shaders.shader";

int run_grid_simulation()
{
	const float grid_resolution = 2.f / 20; // from -1 to 1 there are N cells
	const int intermediate_points = 1;
	const int grid_points_x = 100;
	const int grid_points_y = 100;

	auto* program = new GridVisualization(
		{ -grid_points_x * grid_resolution / 2, -grid_points_x * grid_resolution / 2 },
		{ grid_resolution, grid_resolution },
		grid_points_x, grid_points_y,
		intermediate_points
	);

	return ProgramInputHandler::RunProgram(program, shader_path, 700, 700);
}

int run_space_metric_grid()
{
    ProgramInputHandler::renderer_light_textured.SetGlobalScale({6 / 8.f, 1, 1});
    return ProgramInputHandler::RunProgram(new SpaceMetricGrid(60.f), shader_path, 800, 600);
}

int run_multiple_3d_objects()
{
	return ProgramInputHandler::RunProgram(new ProgramMultipleObjects(60.f), shader_path, 800, 600);
}

int main()
{
	return run_multiple_3d_objects();
}
