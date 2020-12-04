#pragma once

#include "Program.h"
#include "basic_3d_objects/Sphere.h"
#include "basic_3d_objects/Dodecahedron.h"
#include "basic_3d_objects/Surface.h"
#include "basic_3d_objects/AxisObject.h"
#include "SphericalCamera.h"

// to reset console output
#include "Windows.h"


class ProgramMultipleObjects : public Program
{
	// to reset console
	HANDLE console_handle_;

	// all objects
	ThreeAxis* axis_;
	Object3D* draw_objects_[5];

	// control camera with spherical coordinates
	static bool s_update_camera_;
    static SphericalCamera* s_camera_controller_;

public:
	explicit ProgramMultipleObjects(float fps);

	static Program::ProgramState HandlePlus(Program*);
	static Program::ProgramState HandleMinus(Program*);
	static Program::ProgramState HandlePerspectiveMode(Program*);
	static Program::ProgramState HandleOrthogonalMode(Program*);

	static float TaskSurfaceFunction(float x, float y) ;

	int Init() override;
	int Step() override;
};

