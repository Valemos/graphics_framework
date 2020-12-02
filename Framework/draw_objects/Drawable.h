#ifndef INTERFACE_DRAWABLE
#define INTERFACE_DRAWABLE

#include "Renderer.h"
#include "Vector3.h"

class Drawable
{
protected:
    Vector3 object_position_;

    virtual void LoadGlTransform(Renderer& renderer, const Vector3& position) const = 0;

public:
	virtual void InitGlBuffers() = 0;
	virtual void LoadGlBuffers() = 0;

	virtual void Draw(Renderer& renderer) = 0;
	virtual void DrawWireframe(Renderer& renderer) {}

	Vector3& Position(){
        return object_position_;
    }
};


#endif // !INTERFACE_DRAWABLE

