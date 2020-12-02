#include "ProgramInputHandler.h"
#include "SimulationProgram.h"

int main()
{
    return ProgramInputHandler::RunProgram(
            new SimulationProgram(
                    60, -1, { 0.1, 0.01}
            ),
            "D:/coding/c_c++/GraphicalFramework/Framework/framework/shaders/main_shaders.shader",
            600, 600);
}
