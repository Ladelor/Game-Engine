#include "vec4.h"

namespace NumberOne { namespace Math {
	vec4::vec4() : vec3(), w(0.0f)
	{
	}

	vec4::vec4(float x, float y, float z, float w) : vec3(x, y, z), w(w)
	{
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vec)
	{
		stream << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return stream;
	}

	vec4& vec4::add(const vec4& input)
	{
		this->vec3::add(input);
		w += input.w;
		return *this;
	}

	vec4& vec4::sub(const vec4& input)
	{
		this->vec3::sub(input);
		w -= input.w;
		return *this;
	}
	
	vec4& vec4::div(const vec4& input)
	{
		this->vec3::div(input);
		w /= input.w;
		return *this;
	}
	
	vec4& vec4::mult(const vec4& input)
	{
		this->vec3::mult(input);
		w *= input.w;
		return *this;
	}

	vec4& vec4::copy(const vec4& input)
	{
		this->vec3::copy(input);
		w = input.w;
		return *this;
	}

	bool vec4::compare(const vec4& input)
	{
		return (this->vec3::compare(input) && this->w == input.w);
	}

	vec4 operator+(const vec4& vector1, const vec4& vector2)
	{
		return vec4(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z, vector1.w + vector2.w);
	}

	vec4 operator-(const vec4& vector1, const vec4& vector2)
	{
		return vec4(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z, vector1.w - vector2.w);
	}

	vec4 operator*(const vec4& vector1, const vec4& vector2)
	{
		return vec4(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z, vector1.w * vector2.w);
	}

	vec4 operator/(const vec4& vector1, const vec4& vector2)
	{
		return vec4(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z, vector1.w / vector2.w);
	}

	vec4& vec4::operator=(const vec4& vec)
	{
		return this->copy(vec);
	}

	vec4& vec4::operator+=(const vec4& vector)
	{
		return this->add(vector);
	}

	vec4& vec4::operator-=(const vec4& vector)
	{
		return this->sub(vector);
	}

	vec4& vec4::operator*=(const vec4& vector)
	{
		return this->mult(vector);
	}

	vec4& vec4::operator/=(const vec4& vector)
	{
		return this->div(vector);
	}

	bool vec4::operator==(const vec4& vector)
	{
		return this->compare(vector);
	}
} }