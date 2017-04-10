#pragma once

#include "vec2.h"

namespace NumberOne { namespace Math {
	class vec3 : public vec2
	{
	public:
		float z;

		//public member methdos
		vec3();		//empty constructor sets x and y to 0
		vec3(float x, float y, float z);
		friend std::ostream& operator<<(std::ostream& stream, const vec3& vec);

		//arithmetic methods
		vec3& add(const vec3& input);
		vec3& sub(const vec3& input);
		vec3& div(const vec3& input);
		vec3& mult(const vec3& input);
		vec3& copy(const vec3& input);
		bool compare(const vec3& input);

		//arthimetic operators
		friend vec3 operator+(const vec3& vector1, const vec3& vector2);
		friend vec3 operator-(const vec3& vector1, const vec3& vector2);
		friend vec3 operator*(const vec3& vector1, const vec3& vector2);
		friend vec3 operator/(const vec3& vector1, const vec3& vector2);
		vec3& operator=(const vec3& vector);
		vec3& operator+=(const vec3& vector);
		vec3& operator-=(const vec3& vector);
		vec3& operator*=(const vec3& vector);
		vec3& operator/=(const vec3& vector);
		bool operator==(const vec3& vector);
			
	};
} }
 // !VEC3_H
