#include <iostream>

#include "framework/ProgramInputHandler.h"

#include "test_programs/Test2DObject.h"
#include "test_programs/Test3DObject.h"

int main()
{
	//ProgramInputHandler* program = ProgramInputHandler::GetInstance("../Framework/framework/shaders/main_shaders.shader", 800,600);
	//return program->RunProgram(new Test2DProgram(60.f));

	ProgramInputHandler* program = ProgramInputHandler::GetInstance("../Framework/framework/shaders/main_shaders.shader", 800, 600);
	return program->RunProgram(new Test3DObjectsProgram(60.f));
}
