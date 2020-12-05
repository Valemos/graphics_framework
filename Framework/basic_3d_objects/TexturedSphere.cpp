#include "TexturedSphere.h"

TexturedSphere::TexturedSphere(const Texture &texture, const glm::vec3 &edgeColor, const glm::vec3 &figureScale,
                               unsigned detalization)
        : TexturedObject3d(texture, edgeColor, figureScale) {
    detalization_ = detalization;
}

void TexturedSphere::CreateObject() {
    auto mesh_data = Sphere::GetSphereVerticesTriangles(detalization_);
    PackVerticesPrimitives(*mesh_data.first, *mesh_data.second);

    // insert texture coordinates
    auto new_buf = std::vector<float>();
    // number of elements times 2 plus previous elements
    new_buf.reserve((object_buffer_.size() / 6) * 2 + object_buffer_.size());

    auto prev_iter = object_buffer_.begin();

    for (auto* triangle : triangles_){
        auto tex_coords = MapTexture(*mesh_data.first, triangle);
        for (auto& coord : tex_coords){
            new_buf.insert(new_buf.end(), prev_iter, prev_iter + 6);
            prev_iter += 6;

            new_buf.emplace_back(coord.x);
            new_buf.emplace_back(coord.y);
        }
    }

    object_buffer_.clear();
    object_buffer_ = std::vector<float>(new_buf.begin(), new_buf.end());
}

std::vector<Vector3> TexturedSphere::MapTexture(const std::vector<Vector3>& vertices, Triangle *object_triangle) {
    return {{0, 0}, {1, 0}, {0.5, 1}};
}
