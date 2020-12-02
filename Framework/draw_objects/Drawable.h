#ifndef INTERFACE_DRAWABLE
#define INTERFACE_DRAWABLE

class Renderer;

class Drawable
{
protected:
    virtual void LoadGLTransform(Renderer& renderer, const Vector3& position) const = 0;

public:
	virtual void InitGlBuffers() = 0;
	virtual void LoadGlBuffers() = 0;

	virtual void Draw(Renderer& renderer) = 0;
	virtual void DrawWireframe(Renderer& renderer) {}
};

#endif // !INTERFACE_DRAWABLE

