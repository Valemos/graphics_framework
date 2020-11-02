#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


void Camera::UpdateCameraPosition(const Vector3& new_position)
{
	camera_position_ = new_position;
	UpdateViewMatrix();
}

void Camera::UpdateCameraTarget(const Vector3& new_target)
{
	camera_target_ = new_target;
	UpdateViewMatrix();
}

void Camera::UpdateCameraUp(const Vector3& new_camera_up)
{
	camera_direction_ = (camera_position_ - camera_target_).Normal();
	camera_up_ = new_camera_up;
	camera_right_ = camera_up_.Cross(camera_direction_);
	camera_up_ = camera_direction_.Cross(camera_right_);
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	view_matrix_ = lookAt(camera_position_.ToGlm(), camera_target_.ToGlm(), camera_up_.ToGlm());
}

void Camera::set_draw_mode(DrawMode mode)
{
	draw_mode_ = mode;
}

void Camera::set_ortho_minimal_dimention(float dimension)
{
	ortho_minimal_dim = dimension;
}

const Vector3& Camera::get_position() const
{
	return camera_position_;
}

const Vector3& Camera::get_target() const
{
	return camera_target_;
}

const Vector3& Camera::get_up() const
{
	return camera_up_;
}

const Vector3& Camera::get_direction() const
{
	return camera_direction_;
}

const glm::mat4& Camera::get_view_matrix() const
{
	return view_matrix_;
}

glm::mat4 Camera::get_perspective_projection(float aspect_ratio) const
{
	return glm::perspective(field_of_view_, aspect_ratio, near_plane_, far_plane_);
}

glm::mat4 Camera::get_orthogonal_projection(float aspect_ratio) const
{
	return glm::ortho(
		-aspect_ratio * ortho_minimal_dim / 2.f, 
		aspect_ratio * ortho_minimal_dim / 2.f,
		-ortho_minimal_dim / 2.f, 
		ortho_minimal_dim / 2.f,
		near_plane_, far_plane_);
}

glm::mat4 Camera::get_projection(float aspect_ratio) const
{
	if (draw_mode_ == Perspective)
	{
		return get_perspective_projection(aspect_ratio);
	}
	else if (draw_mode_ == Orthogonal)
	{
		return get_orthogonal_projection(aspect_ratio);
	}
}
