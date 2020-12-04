#ifndef GRAPHICALFRAMEWORK_TESTNORMALS_H
#define GRAPHICALFRAMEWORK_TESTNORMALS_H

#include <basic_3d_objects/Cube.h>
#include "Program.h"
#include "Cube.h"
#include "Object3D.h"

class TestNormals : public Program
{

public:
    TestNormals(float fps, std::string name);

    int Init() override;
    int Step() override;
};

TestNormals::TestNormals(float fps, std::string name = "") : Program(fps, name) {

}

int TestNormals::Init() {
    Cube cube(
            {1, 1, 1},
            {0, 0, 0});
    cube.InitGlBuffers();
    return program_continue;
}

int TestNormals::Step() {
    return program_finish;
}

#endif //GRAPHICALFRAMEWORK_TESTNORMALS_H
