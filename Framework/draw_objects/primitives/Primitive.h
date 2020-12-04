#ifndef GL_LAB1_PRIMITIVE
#define GL_LAB1_PRIMITIVE

#include <vector>

class Primitive
{
public:
	explicit Primitive(const std::vector<unsigned int>& indices);
	virtual ~Primitive() = default;

	// we must create set of triangles for each primitive
	virtual void Draw(const void* offset) const = 0;
	virtual std::vector<unsigned> get_triangle_indices() const = 0;
	virtual unsigned get_triangle_indices_count() const = 0;

	virtual void DrawBorder(const void* offset) const;
	const std::vector<unsigned>& get_indices() const;
	void set_indices(const std::vector<unsigned>& indices_new);

protected:
	// all primitives can have different number of points included
	std::vector<unsigned int> indices_;
};

#endif
