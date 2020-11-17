
#include "ProgramInputHandler.h"

#include "programs_source/Test2DObject.h"
#include "programs_source/Test3DObject.h"
#include "programs_source/ProgramMultipleObjects.h"
#include "programs_source/GridVisualization.h"
#include "programs_source/SpaceMetricGrid.h"

const char* shader_path = "D:/coding/c_c++/GraphicalFramework/Framework/framework/shaders/main_shaders.shader";

int run_2d_test()
{
	return ProgramInputHandler::RunProgram(new Test2DProgram(60.f), shader_path, 800, 600);
}

int run_3d_test()
{
	return ProgramInputHandler::RunProgram(new Test3DObjectsProgram(60.f), shader_path, 800, 600);
}

int run_gravity_simulation()
{
	const float grid_resolution = 2.f / 5; // from -1 to 1 there are N cells
	const int intermediate_points = 1;
	const int grid_points_x = 10;
	const int grid_points_y = 10;

	auto* program = new GridVisualization(
		{ -grid_points_x * grid_resolution / 2, -grid_points_x * grid_resolution / 2 },
		{ grid_resolution, grid_resolution },
		grid_points_x, grid_points_y,
		intermediate_points
	);
	
	return ProgramInputHandler::RunProgram(program, shader_path, 700, 700);
}

int run_multiple_3d_objects()
{
	return ProgramInputHandler::RunProgram(new ProgramMultipleObjects(60.f), shader_path, 800, 600);
}

int run_space_metric_grid()
{
	ProgramInputHandler::renderer_.SetGlobalScale({6 / 8.f, 1, 1});
	return ProgramInputHandler::RunProgram(new SpaceMetricGrid(60.f), shader_path, 800, 600);
}

int main()
{
	// call functions from above to use various programs
	return run_multiple_3d_objects();
}
