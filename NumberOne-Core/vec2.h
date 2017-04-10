#pragma once

#include <iostream>

namespace NumberOne { namespace Math {
	struct vec2 {
		//public member data
		float x, y;

		//public member methods
		vec2();		//empty constructor sets x and y to 0
		vec2(float x, float y);
		friend std::ostream& operator<<(std::ostream& stream, const vec2& vec);
		
		//arithmetic methods
		vec2& add(const vec2& input);
		vec2& sub(const vec2& input);
		vec2& div(const vec2& input);
		vec2& mult(const vec2& input);
		vec2& copy(const vec2& input);
		bool compare(const vec2& input);

		//arthimetic operators
		friend vec2 operator+(const vec2& vector1, const vec2& vector2);
		friend vec2 operator-(const vec2& vector1, const vec2& vector2);
		friend vec2 operator*(const vec2& vector1, const vec2& vector2);
		friend vec2 operator/(const vec2& vector1, const vec2& vector2);
		vec2& operator=(const vec2& vector);
		vec2& operator+=(const vec2& vector);
		vec2& operator-=(const vec2& vector);
		vec2& operator*=(const vec2& vector);
		vec2& operator/=(const vec2& vector);
		bool operator==(const vec2& vector);

		};
} }
 // !VEC2_H
