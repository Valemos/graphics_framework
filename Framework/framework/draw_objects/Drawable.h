#ifndef INTERFACE_DRAWABLE
#define INTERFACE_DRAWABLE

class Renderer;
class Vector3;
class Primitive;

#include <vector>

class Drawable
{
	
protected:
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

	// generates GL buffers and sets up all attributes
	virtual void InitGLBuffer();

	// binds required attributes, binds and loads all data to GL buffers
	virtual void LoadGLBuffers();

	// Draw function can be different in other implementations
	virtual void Draw(const Renderer& renderer, const Vector3& position) = 0;
};

#endif // !INTERFACE_DRAWABLE

