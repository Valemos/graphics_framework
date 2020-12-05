#include "ProgramInputHandler.h"
#include "LightingLab3.h"

int main(){
    return ProgramInputHandler::RunProgram(
            new LightingLab3(60, ""),
            R"(D:\coding\c_c++\GraphicalFramework\Framework\shaders\)",
            600, 600);
}
