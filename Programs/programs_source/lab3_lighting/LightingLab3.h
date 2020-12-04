#ifndef GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
#define GRAPHICALFRAMEWORK_LIGHTINGLAB3_H

#include "Program.h"
#include "Cube.h"
#include "SphericalCamera.h"

class LightingLab3 : public Program {

    Cube* objects_[2]{};

    static SphericalCamera* s_camera_controller_;

public:

    LightingLab3(float fps, std::string name);

    int Init() override;
    int Step() override;
};


#endif //GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
