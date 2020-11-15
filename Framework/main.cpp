#include <iostream>

#include "ProgramInputHandler.h"

#include "test_programs/Test2DObject.h"
#include "test_programs/Test3DObject.h"
#include "../programs/GridVisualization.h"


int Run2DTest()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance("../Framework/framework/shaders/main_shaders.shader", 800, 600);
	return program->RunProgram(new Test2DProgram(60.f));
}

int Run3DTest()
{
	ProgramInputHandler* program = ProgramInputHandler::GetInstance("D:/coding/c_c++/SimpleGraphicalFramework/Framework/framework/shaders/main_shaders.shader", 800, 600);
	return program->RunProgram(new Test3DObjectsProgram(60.f));
}

int RunGravitySimulation()
{
	ProgramInputHandler* program_handler = ProgramInputHandler::GetInstance(
		"D:/coding/c_c++/SimpleGraphicalFramework/Framework/framework/shaders/main_shaders.shader",
		800, 500);

	// scale screen with respect to window size
	ProgramInputHandler::renderer.SetGlobalScale({ 500 / 800,  1, 1 });
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

int main()
{
	// call functions from above to use various programs
	return Run3DTest();
}
