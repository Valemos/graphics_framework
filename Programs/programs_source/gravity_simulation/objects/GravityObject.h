#ifndef GRAVITY_OBJECT
#define GRAVITY_OBJECT

class UniverseConstants;

#include "Vector3.h"

class GravityObject

{
protected:
	Vector3 position_;
	Vector3 speed_;
	float mass_;
	float radius_;

public:

	GravityObject();
	virtual ~GravityObject() = default;

	static float MassGravityEquation(float surface_gravity, float radius, float gravity_constant);
	static float MassDensityEquation(float density, float radius);
	static float GravityEquation(float mass, float radius, float gravity_constant);
	static float DensityMassEquation(float mass, float radius);
	static float RadiusEquation(float mass, float density);
	
	void UpdateSpeed(Vector3 acceleration, const UniverseConstants& constants);
	void UpdatePosition();
	void RevertPosition();

	void SetMass(float mass);
	void SetDensity(float density, const UniverseConstants& constants);
	virtual void SetRadius(float radius);
	void SetSurfaceGravity(float gravity, const UniverseConstants& constants);
	float GetSurfaceGravity(const UniverseConstants& constants) const;
	
	void SetSpeed(Vector3 speed) {
		speed_ = speed;
	}

	const Vector3& Speed() const
	{
		return speed_;
	}

	void SetPosition(Vector3 position) {
		position_ = position;
	}
	
	const Vector3& GetPosition() const {
		return position_;
	}

	float GetMass() const {
		return mass_;
	}
	
	float GetRadius() const {
		return radius_;
	}
};


#endif // !GRAVITY_OBJECT
