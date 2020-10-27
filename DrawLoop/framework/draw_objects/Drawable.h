#ifndef INTERFACE_DRAWABLE
#define INTERFACE_DRAWABLE

class Renderer;

class Drawable
{
	
protected:
	GLuint vertex_buffer_id_ = 0;
	std::vector<float> vertex_buffer_;

	// for reuse points from VBO with glDrawElements
	GLuint index_buffer_id_ = 0;
	std::vector<unsigned int> index_buffer_;
	
	GLuint vertex_array_object_id_ = 0;
	
public:
	virtual ~Drawable() = default;
	
	// we must call this function once
	// before all Draw calls
	// loads all necessary data to graphics card
	virtual void UpdateGLBuffer() = 0;
	virtual void Draw(const Renderer& renderer, const Vector3& position) = 0;
};

#endif // !INTERFACE_DRAWABLE

