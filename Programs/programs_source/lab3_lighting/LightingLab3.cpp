#include "ProgramInputHandler.h"
#include "LightingLab3.h"
#include <vector>
#include "Sphere.h"
#include "Surface.h"

SphericalCamera* LightingLab3::s_camera_controller_ = nullptr;

float TaskSurfaceFunction(float x, float y){
    return sin(x) * sqrt(y);
}


LightingLab3::LightingLab3(float fps, std::string name) : Program(fps, name)
{
}

int LightingLab3::Init() {

    objects_[0] = new Sphere(
            (Vector3{97, 194, 45} / 255).ToGlm(),
            {0, 0, 0},
            4);
    objects_[0]->Position() = {0, 0, 0};
    objects_[0]->CreateObject();

    // create values for Surface object
    const float plot_step = 0.2f;
    const int x_count = 50;
    const int y_count = 50;

    std::vector<std::vector<float>> values;
    values.resize(y_count);

    for (float y = 0; y < y_count;)
    {
        values[y].resize(x_count, 0);
        for (float x = 0; x < x_count;)
        {
            values[y][x] = TaskSurfaceFunction(x * plot_step, y * plot_step);
            x += 1.f;
        }
        y += 1.f;
    }

    objects_[1] = new Surface(
            values,
            (Vector3{255, 146, 56} / 255).ToGlm(),
            {0, 0, 0},
            {2, 2, 2});
    objects_[1]->Position() = {-1, -2, -1};
    objects_[1]->CreateObject();


    /// init camera
    s_camera_controller_ = new SphericalCamera(ProgramInputHandler::renderer.get_camera(),
                                               {0, 0, 0},
                                               {0, 1, 0},
                                               10,
                                               270.f,
                                               60.f);
    s_camera_controller_->get_camera().set_draw_mode(DrawMode::Perspective);

    Vector3 pos = {-5, 5, -5};
    ProgramInputHandler::renderer.light_source.position = pos;
    cur_light_angle_ = atan2(pos.z, pos.x);



    ProgramInputHandler::renderer.light_source.color = {1, 1, 1};

    ProgramInputHandler::SetClearColor(0, 10, 50);
    return program_continue;
}

int LightingLab3::Step() {

    s_camera_controller_->MoveCamera(*ProgramInputHandler::keyboard_move_dir);

    auto pos = ProgramInputHandler::renderer.light_source.position;
    pos.y = 0;
    auto radius = pos.Length();
    cur_light_angle_ += 0.05;
    if (cur_light_angle_ > pi2){
        cur_light_angle_ -= pi2;
    }
    pos.x = radius * cos(cur_light_angle_);
    pos.z = radius * sin(cur_light_angle_);

    ProgramInputHandler::renderer.light_source.position = pos;

    for (auto* cube : objects_){
        if (cube != nullptr){
            cube->Draw(ProgramInputHandler::renderer);
        }
    }

    return ProgramInputHandler::HandleButtons(this);
}
