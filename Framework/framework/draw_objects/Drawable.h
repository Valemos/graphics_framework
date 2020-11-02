#ifndef INTERFACE_DRAWABLE
#define INTERFACE_DRAWABLE
#include "Vector3.h"

class Renderer;
class Primitive;

#include <vector>
#include "Vector3.h"


class Drawable
{
	
protected:
	Vector3 object_position_;
	
	unsigned int vertex_buffer_id_ = 0;
	std::vector<float> vertex_buffer_;

	// for reuse points from VBO with glDrawElements
	unsigned int index_buffer_id_ = 0;
	std::vector<unsigned int> index_buffer_;
	
	unsigned int vertex_array_object_id_ = 0;

	std::vector<Primitive*> primitives;
	
public:
	virtual ~Drawable();

	// we must call this function at least once before all Draw calls
	// loads all necessary data to graphics card
	void InitBuffers(const std::vector<Vector3>& vertices, const std::vector<Primitive*>& primitives);
	
	void set_vertices(const std::vector<Vector3>& vertices);
	void set_primitives(const std::vector<Primitive*>& new_primitives);

	virtual Vector3& Position();
	
	// generates GL buffers and sets up all attributes
	virtual void InitGLBuffer();

	// binds required attributes, binds and loads all data to GL buffers
	virtual void LoadGLBuffers();

	// Draw function can be different in other implementations
	virtual void Draw(Renderer& renderer) = 0;

	// Draw function can be different in other implementations
	virtual void DrawWireframe(Renderer& renderer) {};
};

#endif // !INTERFACE_DRAWABLE

