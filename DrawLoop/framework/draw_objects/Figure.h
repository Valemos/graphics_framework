#ifndef GL_LAB1_FIGURE
#define GL_LAB1_FIGURE

#include <vector>
#include <string>
#include "Vector3.h"
#include "../Renderer.h"
#include "Primitive.h"
#include "Drawable.h"

#include <glm/glm.hpp>

class Renderer;

class Figure : public Drawable
{
	glm::vec3 fill_color;
	glm::vec3 border_color;
	glm::vec3 figure_scale;

public:
    std::string name;

	Figure();
	~Figure() override = default;

	void set_fill_color(float r, float g, float b);
	void set_border_color(float r, float g, float b);
	void set_scale(float x_scale, float y_scale, float z_scale = 1.f);

	void set_vertices(const std::vector<Vector3>& vertices);
	void set_primitives(const std::vector<Primitive*>& new_primitives);

    void UpdateGLBuffer() override;
    void Draw(const Renderer& renderer, const Vector3& position) override;
	
private:
	std::vector<Primitive*> primitives;
};

#endif // !GL_LAB1_FIGURE
