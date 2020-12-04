#include <GL/glew.h>
#include "VertexPrimitives.h"


VertexPrimitives::~VertexPrimitives() {
    for(auto* prim : primitives_)
    {
        delete prim;
    }
    vertex_buffer_.clear();
    index_buffer_.clear();
}

void VertexPrimitives::SetVertexBuffer(const std::vector<Vector3>& vertices)
{
    vertex_buffer_.clear();
    vertex_buffer_.reserve(vertices.size() * 3);
    for (const Vector3& vertex : vertices)
    {
        vertex_buffer_.push_back(vertex.x);
        vertex_buffer_.push_back(vertex.y);
        vertex_buffer_.push_back(vertex.z);
    }
}

void VertexPrimitives::SetPrimitives(const std::vector<Primitive*>& new_primitives)
{
    // we create triangles for each primitive

    for (auto* prim : primitives_)
    {
        delete prim;
    }
    primitives_.clear();
    primitives_ = new_primitives;


    unsigned indices_count = 0;
    for (auto* prim : primitives_)
    {
        indices_count += prim->get_indices().size();
    }

    index_buffer_.clear();
    index_buffer_.reserve(indices_count);

    for (auto* prim : primitives_)
    {
        auto indices = prim->get_indices();
        index_buffer_.insert(index_buffer_.end(), indices.begin(), indices.end());
    }
}

std::vector<Triangle*>& VertexPrimitives::GetTriangles(const std::vector<Primitive *> &primitives) {

    for (auto* triangle : triangles_){
        delete triangle;
    }
    triangles_.clear();
    triangles_.reserve(primitives.size());

    for (auto* prim : primitives) {
        auto indices = prim->get_triangle_indices();
        for (auto it = indices.begin(); it != indices.end(); it += 3){
            triangles_.emplace_back(new Triangle(std::vector<unsigned>(it, (it + 3))));
        }
    }
    return triangles_;
}
