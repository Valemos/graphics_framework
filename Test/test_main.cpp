
#include "TestNormals.h"
#include "ProgramInputHandler.h"

int main(){
    return ProgramInputHandler::RunProgram(
            new TestNormals(60),
            R"(D:\coding\c_c++\GraphicalFramework\Framework\shaders\lighting_shaders.shader)",
            600, 600);
}
