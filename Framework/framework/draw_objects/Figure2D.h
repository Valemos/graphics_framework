#ifndef GL_LAB1_FIGURE
#define GL_LAB1_FIGURE

#include <string>
#include "Vector3.h"
#include "../Renderer.h"
#include "Drawable.h"
#include <glm/glm.hpp>


class Figure2D : public Drawable
{
	glm::vec3 fill_color;
	glm::vec3 border_color;
	glm::vec3 figure_scale;

public:
    std::string name;

	Figure2D();
	~Figure2D() override = default;

	void set_fill_color(float r, float g, float b);
	void set_border_color(float r, float g, float b);
	void set_scale(float x_scale, float y_scale, float z_scale = 1.f);

	// before Draw must initialize primitives and load buffers to OpenGL
    void Draw(const Renderer& renderer, const Vector3& position) override;
};

#endif // !GL_LAB1_FIGURE
