#pragma once

#include <sstream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Camera.h"
#include "Vector3.h"

enum class DrawMode
{
	Perspective = 0, Orthogonal = 1
};

class Camera
{
	DrawMode draw_mode_ = DrawMode::Perspective;
	
	glm::mat4 view_matrix_{};
	Vector3 camera_position_;
	Vector3 camera_target_;
	Vector3 camera_direction_;
	Vector3 camera_up_;
	Vector3 camera_right_;

	const float field_of_view_ = glm::radians(45.f);
	const float near_plane_ = 0.1f;
	const float far_plane_ = 100.f;
	
	float ortho_minimal_dim = 2.f;
	
public:
	
	Camera(const Vector3& camera_position, const Vector3& camera_target, const Vector3& camera_up = { 0, 1, 0 })
		: camera_position_(camera_position),
		  camera_target_(camera_target),
		  view_matrix_(glm::identity<glm::mat4>())
	{
		UpdateCameraUp(camera_up);
		UpdateViewMatrix();
	}

	void UpdateCameraPosition(const Vector3& new_position);
	void UpdateCameraTarget(const Vector3& new_target);
	void UpdateCameraUp(const Vector3& new_camera_up);
	void UpdateViewMatrix();

	void set_draw_mode(DrawMode mode);
	void SetOrthoMinimalDimention(float dimension);
	const Vector3& get_position() const;
	const Vector3& get_target() const;
	const Vector3& get_up() const;
	const Vector3& get_direction() const;
	
	const glm::mat4& get_view_matrix() const;
	glm::mat4 get_perspective_projection(float aspect_ratio) const;
	glm::mat4 get_orthogonal_projection(float aspect_ratio) const;
	glm::mat4 GetProjection(float aspect_ratio) const;
	std::string Str() const;
};
