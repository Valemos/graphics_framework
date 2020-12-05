#ifndef GRAPHICALFRAMEWORK_TEXTUREDOBJECT3D_H
#define GRAPHICALFRAMEWORK_TEXTUREDOBJECT3D_H

#include "Object3D.h"
#include "Texture.h"

class TexturedObject3d : public Object3D {
    const Texture& texture_;

public:
    TexturedObject3d(const Texture &texture, const glm::vec3 &edgeColor, const glm::vec3 &figureScale);

    void InitGlBuffers() override;
    void LoadGlBuffers() override;

protected:
    void LoadGlObjectProperties(Renderer &renderer) const override;
};


#endif //GRAPHICALFRAMEWORK_TEXTUREDOBJECT3D_H
