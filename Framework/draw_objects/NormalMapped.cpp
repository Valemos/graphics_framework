#include <draw_objects/primitives/Triangle.h>
#include "NormalMapped.h"

std::vector<Vector3>& NormalMapped::GetNormals(
        const std::vector<Vector3>& vertices,
        const std::vector<Triangle*>& triangles) {

    // reserve space for normals
    normals_.clear();
    normals_.reserve(triangles.size() * 3);

    // calculate normals for each vertex in triangles
    for (auto* triangle : triangles){

        auto& indices = triangle->get_indices();
        auto norm = NormalFromPoints(
                    vertices[indices[0]],
                    vertices[indices[1]],
                    vertices[indices[2]]
                    );
        normals_.emplace_back(norm);
        normals_.emplace_back(norm);
        normals_.emplace_back(norm);
    }

    return normals_;
}

Vector3 NormalMapped::NormalFromPoints(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3) {
    return (p3 - p2).Cross(p1 - p2);
}
