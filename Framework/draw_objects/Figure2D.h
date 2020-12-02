#ifndef GL_LAB1_FIGURE
#define GL_LAB1_FIGURE

#include <string>
#include "Vector3.h"
#include "../Renderer.h"
#include "Drawable.h"
#include <glm/glm.hpp>
#include "VertexPrimitives.h"


class Figure2D : public Drawable, public VertexPrimitives
{

protected:
	glm::vec3 figure_scale_ {1, 1, 1};
	glm::vec3 fill_color_ {0, 0, 0};
	glm::vec3 border_color_ { 0, 0, 0 };
	float border_width_ = 1.f;

public:
    std::string name;

	Figure2D() = default;
	~Figure2D() = default;

	void SetFillColor(float r, float g, float b);
	void SetBorderColor(float r, float g, float b);
	void SetBorderWidth(float w);
	void SetScale(float x_scale, float y_scale, float z_scale = 1.f);

	// before Draw must initialize primitives and load buffers to OpenGL
	void LoadGlTransform(Renderer& renderer, const Vector3& position) const override;
    void Draw(Renderer& renderer) override;
	void DrawWireframe(Renderer& renderer) override;

    void InitGlBuffers() override;
    void LoadGlBuffers() override;
};

#endif // !GL_LAB1_FIGURE
