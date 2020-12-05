#pragma once

#include "Drawable.h"
#include "Vector3.h"
#include <glm/glm.hpp>
#include "VertexPrimitives.h"
#include "NormalMapped.h"

class Object3D : public Drawable, public VertexPrimitives, public NormalMapped
{
protected:
    void LoadGlObjectProperties(Renderer &renderer) const override;
    void LoadGlTransform(Renderer &renderer, const Vector3 &position) const override;
    virtual void LoadGlLightSources(Renderer &renderer) const;

    unsigned object_buffer_id_ = -1;
    unsigned one_object_floats_ = 1;
    std::vector<float> object_buffer_;
public:
	glm::vec3 primary_color{};
	glm::vec3 edge_color{};
	glm::vec3 figure_scale{};

	Object3D(glm::vec3 surface_color, glm::vec3 edge_color, glm::vec3 figure_scale = {1, 1, 1}) :
		primary_color(surface_color), edge_color(edge_color), figure_scale(figure_scale) {}

    // this function must be implemented in every object
    // to initialize all primitives and vertices
    virtual void CreateObject() = 0;

    void PackVerticesPrimitives(const std::vector<Vector3> &vertices, const std::vector<Primitive*> &primitives);

    void Draw(Renderer& renderer) override;
	void DrawWireframe(Renderer& renderer) override;

    void InitGlBuffers() override;
    void LoadGlBuffers() override;
};
