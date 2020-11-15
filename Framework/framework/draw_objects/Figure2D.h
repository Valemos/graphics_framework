#ifndef GL_LAB1_FIGURE
#define GL_LAB1_FIGURE

#include <string>
#include "Vector3.h"
#include "../Renderer.h"
#include "Drawable.h"
#include <glm/glm.hpp>


class Figure2D : public Drawable
{
	glm::vec3 figure_scale_ {1, 1, 1};
	glm::vec3 fill_color_;
	glm::vec3 border_color_;
	float border_width_ = 1.f;

public:
    std::string name;

	Figure2D();
	~Figure2D() override = default;

	void SetFillColor(float r, float g, float b);
	void SetBorderColor(float r, float g, float b);
	void SetBorderWidth(float w);
	void SetScale(float x_scale, float y_scale, float z_scale = 1.f);

	// before Draw must initialize primitives and load buffers to OpenGL
	void LoadGLTransform(Renderer& renderer, const Vector3& position) const override;
    void Draw(Renderer& renderer) override;
	void DrawWireframe(Renderer& renderer) override;
};

#endif // !GL_LAB1_FIGURE
