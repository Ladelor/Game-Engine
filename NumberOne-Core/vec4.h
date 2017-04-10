#pragma once

#include "vec3.h"

namespace NumberOne { namespace Math {
	class vec4 : public vec3
	{
	public:
		float w;

		//public member methdos
		vec4();		//empty constructor sets x and y to 0
		vec4(float x, float y, float z, float w);
		friend std::ostream& operator<<(std::ostream& stream, const vec4& vec);

		//arithmetic methods
		vec4& add(const vec4& input);
		vec4& sub(const vec4& input);
		vec4& div(const vec4& input);
		vec4& mult(const vec4& input);
		vec4& copy(const vec4& input);
		bool compare(const vec4& input);

		//arthimetic operators
		friend vec4 operator+(const vec4& vector1, const vec4& vector2);
		friend vec4 operator-(const vec4& vector1, const vec4& vector2);
		friend vec4 operator*(const vec4& vector1, const vec4& vector2);
		friend vec4 operator/(const vec4& vector1, const vec4& vector2);
		vec4& operator=(const vec4& vector);
		vec4& operator+=(const vec4& vector);
		vec4& operator-=(const vec4& vector);
		vec4& operator*=(const vec4& vector);
		vec4& operator/=(const vec4& vector);
		bool operator==(const vec4& vector);

	};
} }
 // !VEC4_H
