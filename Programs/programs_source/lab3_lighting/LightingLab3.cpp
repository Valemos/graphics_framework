#include <ProgramInputHandler.h>
#include "LightingLab3.h"
#include <vector>

LightingLab3::LightingLab3(float fps, std::string name) : Program(fps, name)
{
}

int LightingLab3::Init() {

    cubes_[0] = new Cube(
            (Vector3{255, 146, 56} / 255).ToGlm(),
            {0, 0, 0}
            );
    cubes_[0]->Position() = {1, 0, 0};

    // create second cube untouched by lighting
    renderer_no_lighting_.LoadShadersFromFile(R"(D:\coding\c_c++\GraphicalFramework\Framework\shaders\main_shaders.shader)");

    cubes_[1] = new Cube(
            (Vector3{255, 146, 56} / 255).ToGlm(),
            {0, 0, 0}
            );
    cubes_[1]->Position() = {-2, 0, 0};

    /// init cameras
    setup_camera(renderer_no_lighting_.get_camera());
    setup_camera(ProgramInputHandler::renderer.get_camera());

    ProgramInputHandler::SetClearColor(57, 103, 173);
    return program_continue;
}

void LightingLab3::setup_camera(Camera &camera) {
    camera.UpdateCameraPosition({6, 3, 5});
    camera.UpdateCameraTarget({0, 0, 0});
    camera.UpdateCameraUp({0, 1, 0});
    camera.set_draw_mode(DrawMode::Perspective);
}

int LightingLab3::Step() {
    ProgramInputHandler::ClearScreen();

    cubes_[0]->Draw(ProgramInputHandler::renderer);
    cubes_[1]->Draw(renderer_no_lighting_);

    return program_continue;
}

