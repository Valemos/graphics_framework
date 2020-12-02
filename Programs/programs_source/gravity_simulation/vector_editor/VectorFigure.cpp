#include "VectorFigure.h"

#include <GL/glew.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer.h"
#include "draw_objects/primitives/Triangle.h"
#include "draw_objects/primitives/TriangleFan.h"

VectorFigure::VectorFigure(Vector3 color, float length, float width)
{
	SetFillColor(color.x, color.y, color.z);
	SetBorderColor(0, 0, 0);

	rotation_angle_ = 0;
	length_ = 1;
	width_ = width;
	point_start_ = { 0, 0};
	point_end_ = { length_, 0};

    InitPrimitiveBuffers(
            {
                    {0, 0},
                    {width_, -width_ / 2},
                    point_end_,
                    {width_, width_ / 2}
            },
            {
                    new TriangleFan({0, 1, 2, 3})
            });
}

void VectorFigure::SetStart(Vector3 start)
{
	point_start_ = start;
	object_position_ = start;
	length_ = point_start_.Distance(point_end_);
	point_end_ = Vector3{ 1, 0}.Rotate(0, 0, rotation_angle_) * length_ + start;
}

void VectorFigure::SetEnd(Vector3 end)
{
	point_end_ = end;
	length_ = point_start_.Distance(point_end_);
	figure_scale_ = { length_, length_, 1};
	const auto direction = point_start_.Direction(point_end_, length_);
	rotation_angle_ = atan2(direction.y, direction.x);
}

Vector3 VectorFigure::GetStart() const
{
	return point_start_;
}

Vector3 VectorFigure::GetEnd() const
{
	return point_end_;
}

void VectorFigure::LoadGlTransform(Renderer& renderer, const Vector3& position) const
{
	const unsigned int shader_program = renderer.get_shader_program();
	static const auto transform_loc = glGetUniformLocation(shader_program, "transform");

	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);
	transform = translate(transform, position.Scale(Vector3::FromGlm(renderer.GetGlobalScale())).ToGlm());
	transform = scale(transform, figure_scale_);
	transform = scale(transform, renderer.GetGlobalScale());

	static const float pi = 3.14159;
	transform = rotate(transform, rotation_angle_ + pi, {0, 0, 1});
	glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(transform));
}
