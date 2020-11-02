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

	// work with other vectors
	float DistanceSquared(const Vector3& other) const;
	float Distance(const Vector3& other) const;
	Vector3 Direction(const Vector3& other) const;
	Vector3 Direction(const Vector3& other, float distance_sqr) const;

	float ScalarMultiply(const Vector3& other) const;
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


	Vector3& operator=(const Vector3& other) = default;
	Vector3& operator=(const glm::vec3& other);
	
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


#endif // !GRAVITY_SIMULATION_VECTOR
