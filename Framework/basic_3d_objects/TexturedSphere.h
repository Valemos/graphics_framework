#ifndef GRAPHICALFRAMEWORK_TEXTUREDSPHERE_H
#define GRAPHICALFRAMEWORK_TEXTUREDSPHERE_H

#include "TexturedObject3d.h"
#include "Sphere.h"

class TexturedSphere : public TexturedObject3d {

    unsigned int detalization_;
public:
    TexturedSphere(const Texture &texture, const glm::vec3 &edgeColor, const glm::vec3 &figureScale,
                   unsigned detalization);

    std::vector<Vector3> MapTexture(const std::vector<Vector3>& vertices, Triangle* object_triangle);

    void CreateObject() override;
};


#endif //GRAPHICALFRAMEWORK_TEXTUREDSPHERE_H
