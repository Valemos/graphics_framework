#ifndef GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
#define GRAPHICALFRAMEWORK_LIGHTINGLAB3_H

#include <draw_objects/Texture.h>
#include "Program.h"
#include "Cube.h"
#include "SphericalCamera.h"

class LightingLab3 : public Program {

    float cur_light_angle_ = 0;

    Texture* grass_texture_ = nullptr;
    Object3D* objects_[2]{};

    static SphericalCamera* s_camera_controller_;

public:

    LightingLab3(float fps, std::string name);

    int Init() override;
    int Step() override;
};


#endif //GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
