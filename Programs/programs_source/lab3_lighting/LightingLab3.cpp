#include "ProgramInputHandler.h"
#include "LightingLab3.h"
#include <vector>
#include "Surface.h"
#include "TexturedSphere.h"

SphericalCamera* LightingLab3::s_camera_controller_ = nullptr;
bool LightingLab3::s_update_camera_ = false;


float TaskSurfaceFunction(float x, float y){
    return sin(x) * sqrt(y);
}


LightingLab3::LightingLab3(float fps, std::string name) : Program(fps, name)
{
    ProgramInputHandler::AddButtonHandlers({
        ButtonHandler(Key::Minus, HandleMinus),
        ButtonHandler(Key::Equal, HandlePlus)
    });
}

int LightingLab3::Init() {

    grass_texture_ = new Texture(R"(D:\coding\c_c++\GraphicalFramework\Programs\programs_source\lab3_lighting\grass.jpg)");
    grass_texture_->Create();


    objects_.reserve(2);
    objects_.emplace_back(
            new TexturedSphere(
                *grass_texture_,
                {0, 0, 0},
                {1, 1, 1},
                4));
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

    objects_.push_back(
            new Surface(
                values,
                (Vector3{255, 146, 56} / 255).ToGlm(),
                {0, 0, 0},
                {2, 2, 2}));
    objects_[1]->Position() = {-1, -2, -1};
//    objects_.push_back(new Cube(
//            (Vector3{219, 118, 50} / 255.f).ToGlm(),
//            {0, 0, 0}
//            ));

    objects_[1]->CreateObject();


    /// init camera
    s_camera_controller_ = new SphericalCamera(
            {0, 0, 0},
            {0, 1, 0},
            10,
            270.f,
            60.f,
            0.1);
    ProgramInputHandler::renderer_light_textured.get_camera().set_draw_mode(DrawMode::Perspective);
    ProgramInputHandler::renderer_light_color.get_camera().set_draw_mode(DrawMode::Perspective);

    s_camera_controller_->UpdateCamera(ProgramInputHandler::renderer_light_textured.get_camera());
    s_camera_controller_->UpdateCamera(ProgramInputHandler::renderer_light_color.get_camera());

    Vector3 pos = {-10, 5, -10};
    ProgramInputHandler::renderer_light_textured.light_source.position = pos;
    cur_light_angle_ = atan2(pos.z, pos.x);

    ProgramInputHandler::renderer_light_textured.light_source.color = {1, 1, 1};
    ProgramInputHandler::renderer_light_color.light_source.color = {1, 1, 1};


    ProgramInputHandler::SetClearColor(0, 10, 50);
    return program_continue;
}

int LightingLab3::Step() {

    if (s_camera_controller_->MoveCamera(*ProgramInputHandler::keyboard_move_dir) ||
        s_update_camera_){

        s_camera_controller_->UpdateCamera(ProgramInputHandler::renderer_light_textured.get_camera());
        s_camera_controller_->UpdateCamera(ProgramInputHandler::renderer_light_color.get_camera());

        s_update_camera_ = false;
    }

    auto pos = ProgramInputHandler::renderer_light_textured.light_source.position;
    pos.y = 0;
    auto radius = pos.Length();
    cur_light_angle_ += 0.05;
    if (cur_light_angle_ > pi2){
        cur_light_angle_ -= pi2;
    }
    pos.x = radius * cos(cur_light_angle_);
    pos.z = radius * sin(cur_light_angle_);

    ProgramInputHandler::renderer_light_textured.light_source.position = pos;
    ProgramInputHandler::renderer_light_color.light_source.position = pos;



    objects_[0]->Draw(ProgramInputHandler::renderer_light_textured);
    objects_[1]->Draw(ProgramInputHandler::renderer_light_color);

    return ProgramInputHandler::HandleButtons(this);
}

Program::ProgramState LightingLab3::HandlePlus(Program *program) {
    LightingLab3::s_camera_controller_->DecrementRadius();
    LightingLab3::s_update_camera_ = true;
    return Program::program_continue;
}

Program::ProgramState LightingLab3::HandleMinus(Program *program){
    LightingLab3::s_camera_controller_->IncrementRadius();
    LightingLab3::s_update_camera_ = true;
    return Program::program_continue;
}
