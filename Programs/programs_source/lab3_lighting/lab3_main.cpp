#include "ProgramInputHandler.h"
#include "LightingLab3.h"

int main(){
    return ProgramInputHandler::RunProgram(
            new LightingLab3(60, ""),
            "",
            600, 600);
}
