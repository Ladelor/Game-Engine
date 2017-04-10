#include "vec2.h"

namespace NumberOne { namespace Math {

	vec2::vec2() : vec2(0.0f, 0.0f)
	{
	}

	vec2::vec2(float x, float y) : x(x), y(y)
	{
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2 (" << vector.x << ", " << vector.y << ")" << std::endl;
		return stream;
	}
	
	vec2& vec2::add(const vec2& input)
	{
		this->x += input.x;
		this->y += input.y;
		return *this;
	}

	vec2& vec2::sub(const vec2& input)
	{
		this->x -= input.x;
		this->y -= input.y;
		return *this;
	}

	vec2& vec2::mult(const vec2& input)
	{
		this->x *= input.x;
		this->y *= input.y;
		return *this;
	}

	vec2& vec2::div(const vec2& input)
	{
		this->x /= input.x;
		this->y /= input.y;
		return *this;
	}

	vec2& vec2::copy(const vec2& input)
	{
		this->x = input.x;
		this->y = input.y;
		return *this;
	}

	bool vec2::compare(const vec2& input)
	{
		return (this->x == input.x && this->y == input.y);
	}

	vec2 operator+(const vec2& vector1, const vec2& vector2)
	{
		return (vec2(vector1.x + vector2.x, vector1.y + vector2.y));
	}

	vec2 operator-(const vec2& vector1, const vec2& vector2)
	{
		return (vec2(vector1.x - vector2.x, vector1.y - vector2.y));
	}

	vec2 operator*(const vec2& vector1, const vec2& vector2)
	{
		return (vec2(vector1.x * vector2.x, vector1.y * vector2.y));
	}

	vec2 operator/(const vec2& vector1, const vec2& vector2)
	{
		return (vec2(vector1.x / vector2.x, vector1.y / vector2.y));
	}

	vec2& vec2::operator=(const vec2& vector)
	{
		return this->copy(vector);
	}

	vec2& vec2::operator+=(const vec2& vector)
	{
		return this->add(vector);
	}

	vec2& vec2::operator-=(const vec2& vector)
	{
		return this->sub(vector);
	}

	vec2& vec2::operator*=(const vec2& vector)
	{
		return this->mult(vector);
	}

	vec2& vec2::operator/=(const vec2& vector)
	{
		return this->div(vector);
	}

	bool vec2::operator==(const vec2& vector)
	{
		return this->compare(vector);
	}
} }