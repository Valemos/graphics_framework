#ifndef GRAPHICALFRAMEWORK_VERTEXPRIMITIVES_H
#define GRAPHICALFRAMEWORK_VERTEXPRIMITIVES_H

#include <draw_objects/primitives/Primitive.h>
#include <Vector3.h>
#include <vector>


class VertexPrimitives {

protected:
    Vector3 object_position_;

    unsigned int vertex_buffer_id_ = 0;
    std::vector<float> vertex_buffer_;

    // for reuse points from VBO with glDrawElements
    unsigned int index_buffer_id_ = 0;
    std::vector<unsigned int> index_buffer_;

    unsigned int vertex_array_object_id_ = 0;

    std::vector<Primitive*> primitives_;

public:
    ~VertexPrimitives();

    // we must call this function at least once before all Draw calls
    // loads all necessary data to graphics card
    void SetVertices(const std::vector<Vector3>& vertices);
    void SetPrimitives(const std::vector<Primitive*>& new_primitives);

};


#endif //GRAPHICALFRAMEWORK_VERTEXPRIMITIVES_H
