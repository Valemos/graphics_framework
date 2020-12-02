#ifndef GRAPHICALFRAMEWORK_NORMALPRIMITIVES_H
#define GRAPHICALFRAMEWORK_NORMALPRIMITIVES_H


#include <vector>
#include <Vector3.h>
#include <draw_objects/primitives/Primitive.h>

class NormalPrimitives {

protected:
    std::vector<float> normals_buffer_;

    void SetNormalsFromPrimitives(const std::vector<Vector3> &vertices, const std::vector<Primitive*>& primitives);
};


#endif //GRAPHICALFRAMEWORK_NORMALPRIMITIVES_H
