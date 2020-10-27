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

std::string Vector3::str() const
{
	std::ostringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}

float Vector3::distanceSquared(const Vector3& other) const
{
	float x_temp = x - other.x;
	float y_temp = y - other.y;
	float z_temp = z - other.z;
	return x_temp * x_temp + y_temp * y_temp + z_temp * z_temp;
}

float Vector3::distance(const Vector3& other) const
{
	// returns distance between points
	// to avoid two multiplications, result of this operation is saved
	float x_temp = x - other.x;
	float y_temp = y - other.y;
	float z_temp = z - other.z;
	return sqrt(x_temp * x_temp + y_temp * y_temp + z_temp * z_temp);
}

Vector3 Vector3::direction(const Vector3& other) const
{
	// finds normalized direction vector
	float distance = Vector3::distance(other);
	return Vector3(
		other.x / distance, 
		other.y / distance,
		other.z / distance);
}

Vector3 Vector3::direction(const Vector3& other, float distanceSqr) const
{
	// optimized direction
	// provide with squared distance
	// used to avoid calculating this distance again in some cases
	
	float distance = sqrt(distanceSqr);
	return Vector3(
		(this->x - other.x) / distance, 
		(this->y - other.y) / distance, 
		(this->z - other.z) / distance);
}

float Vector3::scalarMult(const Vector3& other) const
{
	// scalar multiplication of vectors
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

float Vector3::length() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

void Vector3::normalize()
{
	float len = length();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}

Vector3 Vector3::normal() const
{
	float len = length();
	if (len > VECTOR_FLOAT_ACCURACY)
	{
		return Vector3(
			this->x / len,
			this->y / len,
			this->z / len);
	}
	return Vector3();
}

Vector3 Vector3::scale(const Vector3& other) const
{
	return {this->x * other.x,
			this->y * other.y,
			this->z * other.z };
}

Vector3 Vector3::scaleInv(const Vector3& other) const
{
	return { this->x / other.x,
			this->y / other.y,
			this->z / other.z };
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(this->x + other.x, this->x + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(this->x - other.x, this->x - other.y, this->z - other.z);
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 Vector3::operator*(float a) const
{
	return Vector3(this->x * a, this->y * a, this->z * a);
}

Vector3 Vector3::operator/(float a) const
{
	return Vector3(this->x / a, this->y / a, this->z / a);
}
