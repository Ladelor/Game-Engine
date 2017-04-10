#include "vec3.h"

namespace NumberOne { namespace Math {

	vec3::vec3() : vec2(), z(0.0f)
	{
	}

	vec3::vec3(float x, float y, float z) : vec2(x, y), z(z)
	{
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vec)
	{
		stream << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
		return stream;
	}

	vec3& vec3::add(const vec3& input)
	{
		this->vec2::add(input);
		z += input.z;
		return *this;
	}

	vec3& vec3::sub(const vec3& input)
	{
		this->vec2::sub(input);
		z -= input.z;
		return *this;
	}
	vec3& vec3::div(const vec3& input)
	{
		this->vec2::div(input);
		z /= input.z;
		return *this;
	}

	vec3& vec3::mult(const vec3& input)
	{
		this->vec2::mult(input);
		z *= input.z;
		return *this;
	}

	vec3& vec3::copy(const vec3& input)
	{
		this->vec2::copy(input);
		z = input.z;
		return *this;
	}

	bool vec3::compare(const vec3& input)
	{
		return (this->vec2::compare(input) && this->z == input.z);
	}

	vec3 operator+(const vec3& vector1, const vec3& vector2)
	{
		return vec3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
	}

	vec3 operator-(const vec3& vector1, const vec3& vector2)
	{
		return vec3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
	}

	vec3 operator*(const vec3& vector1, const vec3& vector2)
	{
		return vec3(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);
	}

	vec3 operator/(const vec3& vector1, const vec3& vector2)
	{
		return vec3(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z);
	}

	vec3& vec3::operator=(const vec3& vec)
	{
		return this->copy(vec);
	}

	vec3& vec3::operator+=(const vec3& vector)
	{
		return this->add(vector);
	}

	vec3& vec3::operator-=(const vec3& vector)
	{
		return this->sub(vector);
	}

	vec3& vec3::operator*=(const vec3& vector)
	{
		return this->mult(vector);
	}

	vec3& vec3::operator/=(const vec3& vector)
	{
		return this->div(vector);
	}

	bool vec3::operator==(const vec3& vector)
	{
		return this->compare(vector);
	}
} }