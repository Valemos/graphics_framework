#include "CelestialBody.h"

#include "Vector3.h"
#include "draw_objects/TriangleFan.h"
#include "../UniverseConstants.h"


CelestialBody::CelestialBody(const std::string name, Vector3 color, UniverseConstants* constants, float radius, float surfaceGravity, float mass) :
	GravityObject(radius, surfaceGravity, mass, *constants),
	constants_(constants),
	name(name)
{
	circle_ = new Figure2D();
	InitCirclePoints();
	circle_->SetScale(radius, radius);
	circle_->SetFillColor(color.x, color.y, color.z);
	circle_->SetBorderColor(0, 0, 0);
}

CelestialBody* CelestialBody::CheckCollision(const std::vector<CelestialBody*>& bodies)
{
	// we check for collision with any object
	for (auto* body : bodies) {
		if (body != this) {
			float distance = this->Position().Distance(body->Position());
			if (distance < this->Radius() + body->Radius()) {
				return body;
			}
		}
	}

	return nullptr;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CelestialBody::InitCirclePoints()
{
	auto vertices = std::vector<Vector3>();
	auto indices = std::vector<unsigned>();
	vertices.reserve(s_circle_points);
	indices.reserve(s_circle_points);
	
	static const double angle_step = 2.0 * 3.14159265 / s_circle_points;
	double angle = 0.0;
	for (int i = 0; i < s_circle_points; i++)
	{
		vertices.emplace_back(Vector3{ (float)cos(angle), (float)sin(angle) });
		indices.emplace_back(i);
		angle += angle_step;
	}

	circle_->InitBuffers(vertices, {new TriangleFan(indices)});
}

void CelestialBody::Draw(Renderer& renderer) const
{
	circle_->Position() = position_;
	circle_->Draw(renderer);
}

void CelestialBody::Display()
{
	printf("\n-----------\n%s\n-----------\nRadius:\t%.3f\nPos:\tX: %.1f\tY: %.1f\nSpd:\tX: %.2f\tY: %.2f\n", 
		this->name.c_str(),
		this->Radius(),
		this->Position().x,
		this->Position().y,
		this->Speed().x,
		this->Speed().y);
}
