
#include "ProgramInputHandler.h"

#include "programs_source/Test2DObject.h"
#include "programs_source/Test3DObject.h"
#include "programs_source/ProgramMultipleObjects.h"
#include "programs_source/GridVisualization.h"

const char* shader_path = "D:/coding/c_c++/GraphicalFramework/Framework/framework/shaders/main_shaders.shader";

int run_2d_test()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance(shader_path, 800, 600);
	return program->RunProgram(new Test2DProgram(60.f));
}

int run_3d_test()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance(shader_path, 800, 600);
	return program->RunProgram(new Test3DObjectsProgram(60.f));
}

int run_gravity_simulation()
{
	ProgramInputHandler* program_handler = ProgramInputHandler::GetInstance(shader_path,800, 500);

	// scale screen with respect to window size
	ProgramInputHandler::renderer.SetGlobalScale({ 800 / 500,  1, 1 });
	const float grid_resolution = 2.f / 20; // from -1 to 1 there are N cells
	const int grid_points_x = 40;
	const int grid_points_y = 40;

	return program_handler->RunProgram(
		new GridVisualization(
			{ -grid_points_x * grid_resolution / 2, -grid_points_x * grid_resolution / 2 },
			{ grid_resolution, grid_resolution },
			grid_points_x, grid_points_y)
	);
}

int run_multiple_3d_objects()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance(shader_path, 800, 600);
	return program->RunProgram(new ProgramMultipleObjects(60.f));
}

int main()
{
	// call functions from above to use various programs
	return run_3d_test();
}
