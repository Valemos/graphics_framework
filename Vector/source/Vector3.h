#ifndef GRAVITY_SIMULATION_VECTOR
#define GRAVITY_SIMULATION_VECTOR

#include <string>
#include <glm/vec3.hpp>

constexpr float VECTOR_FLOAT_ACCURACY = 0.0000001f;

class Vector3 {

public:
	float x;
	float y;
	float z;

	Vector3(float x = 0.f, float y = 0.f, float z = 0.f);
	~Vector3() = default;
	
	std::string Str() const;
	glm::vec3 ToGlm() const
	{
		return {x, y, z};
	}

	static Vector3 FromGlm(glm::vec3 v)
	{
		return {v.x, v.y, v.z};
	}

	// work with other vectors
	float DistanceSquared(const Vector3& other) const;
	float Distance(const Vector3& other) const;
	Vector3 Direction(const Vector3& other) const;
	Vector3 Direction(const Vector3& other, float distance) const;

	float Dot(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;

	float LengthSqr() const;	
	float Length() const;

	// makes module of vector equal one
	void Normalize();
	Vector3 Normal() const;

	// scales each coordinate respectively
	Vector3 Scale(const Vector3& other) const;

	// inverse operation to scale()
	Vector3 ScaleInv(const Vector3& other) const;

	Vector3 Rotate(float x_angle = 0, float y_angle = 0, float z_angle = 0) const;
	

	Vector3& operator=(const Vector3& other) = default;
	
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(float a) const;
	Vector3 operator/(float a) const;
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);

	// comparison
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
};

inline Vector3 operator*(float a, const Vector3& vec)
{
	return vec * a;
}


#endif // !GRAVITY_SIMULATION_VECTOR
