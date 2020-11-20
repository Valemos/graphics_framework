#pragma once
#include "Vector3.h"
#include "draw_objects/Figure2D.h"

class VectorFigure : public Figure2D
{
	Vector3 point_start_;
	Vector3 point_end_;
	float rotation_angle_;
	float length_;
	float width_;
	
public:
	VectorFigure(Vector3 color, float length = 1.f, float width=0.5f);

	void SetStart(Vector3 start);
	void SetEnd(Vector3 end);
	Vector3 GetStart() const;
	Vector3 GetEnd() const;
	
	void LoadGLTransform(Renderer& renderer, const Vector3& position) const override;
};

