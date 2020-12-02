#ifndef GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
#define GRAPHICALFRAMEWORK_LIGHTINGLAB3_H

#include "Program.h"

class LightingLab3 : public Program {

public:

    LightingLab3(float fps, std::string name);

    int Init() override;
    int Step() override;
};


#endif //GRAPHICALFRAMEWORK_LIGHTINGLAB3_H
