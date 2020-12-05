#ifndef GRAPHICALFRAMEWORK_NORMALMAPPED_H
#define GRAPHICALFRAMEWORK_NORMALMAPPED_H


class Triangle;

#include <vector>
#include <Vector3.h>
#include <draw_objects/primitives/Primitive.h>

class NormalMapped {

protected:
    std::vector<Vector3> normals_;

    // some specific objects can define their normal function
    // and can implement that function for each vertex separately
    virtual std::vector<Vector3>& GetNormals(const std::vector<Vector3> &vertices, const std::vector<Triangle*>& triangles);
    static Vector3 NormalFromPoints(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);
};


#endif //GRAPHICALFRAMEWORK_NORMALMAPPED_H
