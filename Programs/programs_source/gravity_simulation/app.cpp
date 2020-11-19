#include "ProgramInputHandler.h"
#include "programs/SimulateGravityProgram.h"
#include "programs/TestMoveObject.h"

int main(void)
{
	ProgramInputHandler* program = ProgramInputHandler::getInstance(500, 500);

	// swap lines to run differen programs
    return program->RunProgram(new SimulationProgram(60.f, -1, { 0.0001f, 0.0001f }));
}
