#pragma once

#include "ProgramFramework.h"
#include "basic_3d_objects/Sphere.h"
#include "basic_3d_objects/Dodecahedron.h"
#include "basic_3d_objects/Surface.h"
#include "basic_3d_objects/AxisObject.h"

// for resetting console output
#include "Windows.h"

static constexpr float pi = 3.141592653589793f;
static constexpr float pi2 = pi * 2;

class ProgramMultipleObjects : public ProgramFramework
{
	// to reset console
	HANDLE console_handle_;

	// all objects
	ThreeAxis* axis_;
	Object3D* draw_objects_[5];

	// control camera with spherical coordinates
	const float top_angle_ = 0.f;
	const float bot_angle_ = pi;
	float theta_angle_ = 90.f / 180 * pi;
	float phi_angle_ = 90.f / 180 * pi;
	float radius_ = 20.f;

	static const float s_camera_move_speed;
	static float s_increment_zoom_value_;
	Vector3 camera_position_;
	Vector3 camera_up_{ 0, 1, 0 };
	Vector3 camera_down_{ 0, -1, 0 };
	Vector3 current_camera_up_ = camera_up_;

	// controls zoom in orthogonal mode
	float ortho_projection_dim_ = radius_;

public:
	ProgramMultipleObjects(float fps);

	static int HandlePlus(void*);
	static int HandleMinus(void*);
	static int HandlePerspectiveMode(void*);
	static int HandleOrthogonalMode(void*);
	void UpdateCameraSphericalCoordinate();

	float TaskSurfaceFunction(float x, float y) const;

	int Init() override;
	int Step() override;
};

