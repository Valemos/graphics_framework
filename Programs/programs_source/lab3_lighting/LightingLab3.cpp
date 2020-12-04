#include "ProgramInputHandler.h"
#include "LightingLab3.h"
#include <vector>


SphericalCamera* LightingLab3::s_camera_controller_ = nullptr;

LightingLab3::LightingLab3(float fps, std::string name) : Program(fps, name)
{
}

int LightingLab3::Init() {

    objects_[0] = new Cube(
            (Vector3{255, 146, 56} / 255).ToGlm(),
            {0, 0, 0}
            );
    objects_[0]->Position() = {-0.5, -0.5, -0.5};
    objects_[0]->CreateObject();

    objects_[1] = new Cube(
            (Vector3{255, 146, 56} / 255).ToGlm(),
            {0, 0, 0}
            );
    objects_[1]->Position() = {-2, -2, -2};
    objects_[1]->CreateObject();

    /// init camera
    s_camera_controller_ = new SphericalCamera(ProgramInputHandler::renderer.get_camera(),
                                               {0, 0, 0},
                                               {0, 1, 0},
                                               5,
                                               120.f,
                                               60.f);

    s_camera_controller_->get_camera().set_draw_mode(DrawMode::Perspective);

    ProgramInputHandler::renderer.light_source.position = {10, 5, 10};
    ProgramInputHandler::renderer.light_source.color = {1, 1, 1};

    ProgramInputHandler::SetClearColor(0, 10, 50);
    return program_continue;
}

int LightingLab3::Step() {

//    s_camera_controller_->MoveCamera(*ProgramInputHandler::keyboard_move_dir);
    if (ProgramInputHandler::keyboard_move_dir->Length() > VECTOR_FLOAT_ACCURACY){
        ProgramInputHandler::renderer.light_source.position += *ProgramInputHandler::keyboard_move_dir * 0.1;
    }


    for (auto* cube : objects_){
        cube->Draw(ProgramInputHandler::renderer);
    }

    return ProgramInputHandler::HandleButtons(this);
}
