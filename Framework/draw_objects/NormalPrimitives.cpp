#include "NormalPrimitives.h"

void NormalPrimitives::SetNormalsFromPrimitives(const std::vector<Vector3>& vertices, const std::vector<Primitive*>& primitives) {

    // reserve space for normals
    unsigned normals_count = 0;
    for (auto* primitive : primitives){
        normals_count += primitive->get_indices().size();
    }
    normals_buffer_.clear();
    normals_buffer_.reserve(3 * normals_count);

    // calculate normals for each vertex in primitives
    for (auto* primitive : primitives){
        for (int i = 0; i < primitive->get_indices().size(); i++){
            // get two consecutive
        }
    }
}
