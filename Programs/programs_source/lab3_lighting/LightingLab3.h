#ifndef GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
#define GRAPHICALFRAMEWORK_LIGHTINGLAB3_H

#include "Program.h"
#include "Cube.h"

class LightingLab3 : public Program {

    Cube* cubes_[2]{};
    Renderer renderer_no_lighting_{};

public:

    LightingLab3(float fps, std::string name);

    int Init() override;
    int Step() override;

    static void setup_camera(Camera &camera) ;
};


#endif //GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
