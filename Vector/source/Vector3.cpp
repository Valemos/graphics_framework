#include "Vector3.h"
#include <cstdlib>
#include <cmath>
#include <sstream>

Vector3::Vector3(float x, float y, float z)
{
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;
}

std::string Vector3::Str() const
{
	std::ostringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}

float Vector3::DistanceSquared(const Vector3& other) const
{
	const float x_temp = x - other.x;
	const float y_temp = y - other.y;
	const float z_temp = z - other.z;
	return x_temp * x_temp + y_temp * y_temp + z_temp * z_temp;
}

float Vector3::Distance(const Vector3& other) const
{
	// returns distance between points
	// to avoid two multiplications, result of this operation is saved
	const float x_temp = x - other.x;
	const float y_temp = y - other.y;
	const float z_temp = z - other.z;
	return sqrt(x_temp * x_temp + y_temp * y_temp + z_temp * z_temp);
}

Vector3 Vector3::Direction(const Vector3& other) const
{
	// finds normalized direction vector
	const float distance = Distance(other);
	return Vector3(
		(x - other.x) / distance,
		(y - other.y) / distance,
		(z - other.z) / distance);
}

Vector3 Vector3::Direction(const Vector3& other, float distance) const
{
	// optimized direction
	// provide with distance to avoid calculating it again
	return Vector3(
		(x - other.x) / distance, 
		(y - other.y) / distance, 
		(z - other.z) / distance);
}

float Vector3::Dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return { y * other.z - z * other.y , z * other.x - x * other.z, x * other.y - y * other.x};
}

float Vector3::LengthSqr() const
{
	return x * x + y * y + z * z;
}

float Vector3::Length() const
{
	return sqrt(LengthSqr());
}

void Vector3::Normalize()
{
	const float len = Length();
	x /= len;
	y /= len;
	z /= len;
}

Vector3 Vector3::Normal() const
{
	const float len = Length();
	if (len > VECTOR_FLOAT_ACCURACY)
	{
		return Vector3(
			x / len,
			y / len,
			z / len);
	}
	return Vector3();
}

Vector3 Vector3::Scale(const Vector3& other) const
{
	return {x * other.x,
			y * other.y,
			z * other.z };
}

Vector3 Vector3::ScaleInv(const Vector3& other) const
{
	return { x / other.x,
			 y / other.y,
			 z / other.z };
}

Vector3 Vector3::Rotate(float x_angle, float y_angle, float z_angle) const
{
	Vector3 result = *this;
	float cos_value = 0;
	float sin_value = 0;
	
	if (x_angle > VECTOR_FLOAT_ACCURACY)
	{
		cos_value = cos(x_angle);
		sin_value = sin(x_angle);
		result = {
			result.x,
			result.y * cos_value - result.z * sin_value,
			result.y * sin_value + result.z * cos_value
		};
	}

	if (y_angle > VECTOR_FLOAT_ACCURACY)
	{
		cos_value = cos(y_angle);
		sin_value = sin(y_angle);
		result = {
			result.x * cos_value - result.z * sin_value,
			result.y,
			result.x * sin_value + result.z * cos_value
		};
	}

	if (z_angle > VECTOR_FLOAT_ACCURACY)
	{
		cos_value = cos(z_angle);
		sin_value = sin(z_angle);
		result = {
			result.x * cos_value - result.y * sin_value,
			result.x * sin_value + result.y * cos_value,
			result.z
		};
	}

	return result;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return
		(x - other.x) < VECTOR_FLOAT_ACCURACY &&
		(y - other.y) < VECTOR_FLOAT_ACCURACY &&
		(z - other.z) < VECTOR_FLOAT_ACCURACY;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return
		(x - other.x) > VECTOR_FLOAT_ACCURACY ||
		(y - other.y) > VECTOR_FLOAT_ACCURACY ||
		(z - other.z) > VECTOR_FLOAT_ACCURACY;
}

Vector3 Vector3::operator*(float a) const
{
	return Vector3(x * a, y * a, z * a);
}

Vector3 Vector3::operator/(float a) const
{
	return Vector3(x / a, y / a, z / a);
}
