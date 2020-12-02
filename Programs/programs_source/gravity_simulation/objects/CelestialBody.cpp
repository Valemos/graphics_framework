#include "CelestialBody.h"

#include "Vector3.h"
#include "draw_objects/primitives/TriangleFan.h"
#include "../UniverseConstants.h"


CelestialBody::CelestialBody(const std::string name, Vector3 color, UniverseConstants* constants) : GravityObject(),
	constants_(constants), name(name)
{
	circle_ = new Figure2D();
	InitCirclePoints();
	circle_->SetScale(radius_, radius_);
	circle_->SetFillColor(color.x, color.y, color.z);
	circle_->SetBorderColor(0, 0, 0);
}

CelestialBody* CelestialBody::CheckCollision(const std::vector<CelestialBody*>& bodies)
{
	// we check for collision with any object
	for (auto* body : bodies) {
		if (body != this) {
			float distance = this->GetPosition().Distance(body->GetPosition());
			if (distance < this->GetRadius() + body->GetRadius()) {
				return body;
			}
		}
	}

	return nullptr;
}

void CelestialBody::SetRadius(float radius)
{
	// mass stays the same, surface gravity and density changes
	radius_ = radius;
	circle_->SetScale(radius, radius);
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

    circle_->InitPrimitiveBuffers(vertices, {new TriangleFan(indices)});
}

void CelestialBody::Draw(Renderer& renderer) const
{
	circle_->Position() = position_;
	circle_->Draw(renderer);
	circle_->DrawWireframe(renderer);
}

void CelestialBody::Display()
{
	printf("\n-----------\n%s\n-----------\nRadius:\t%.3f\nPos:\tX: %.1f\tY: %.1f\nSpd:\tX: %.2f\tY: %.2f\n", 
		this->name.c_str(),
		this->GetRadius(),
		this->GetPosition().x,
		this->GetPosition().y,
		this->Speed().x,
		this->Speed().y);
}
