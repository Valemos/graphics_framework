#ifndef GRAPHICALFRAMEWORK_VERTEXPRIMITIVES_H
#define GRAPHICALFRAMEWORK_VERTEXPRIMITIVES_H

#include <draw_objects/primitives/Primitive.h>
#include <draw_objects/primitives/Triangle.h>
#include <Vector3.h>
#include <vector>


class VertexPrimitives {

protected:

    unsigned int vertex_buffer_id_ = 0;
    std::vector<float> vertex_buffer_;

    // for reuse points from VBO with glDrawElements
    unsigned int index_buffer_id_ = 0;
    std::vector<unsigned int> index_buffer_;

    unsigned int VAO_id = 0;
    std::vector<Primitive*> primitives_;
    std::vector<Triangle*> triangles_;

public:
    ~VertexPrimitives();

    void SetVertexBuffer(const std::vector<Vector3>& vertices);
    void SetPrimitives(const std::vector<Primitive*>& new_primitives);
    std::vector<Triangle*>& GetTriangles(const std::vector<Primitive*>& primitives);
};


#endif //GRAPHICALFRAMEWORK_VERTEXPRIMITIVES_H
