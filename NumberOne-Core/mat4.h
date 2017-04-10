#pragma once

#include "vec4.h"

#define _USE_MATH_DEFINES
#include <math.h>

//real size will be MATRICE_SIZE^2
#define MATRICE_SIZE 4

namespace NumberOne { namespace Math {
	class mat4
	{
	public:
		float elements[MATRICE_SIZE * MATRICE_SIZE];

		mat4();
		mat4(float diag);
		~mat4() {}

		friend std::ostream& operator<<(std::ostream& stream, const mat4& mat4);
		static float degsToRads(const float degress);

		vec4 getColumn(int column);

		static mat4 identity();

		static mat4 orthographic(float l, float r, float bot, float top, float near, float far);
		static mat4 perspective(float fov, float aspRatio, float near, float far);

		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		//matrice multipliers
		mat4& multiply(const mat4& input);
		friend mat4 operator*(mat4 left, const mat4& right);
		
		mat4& operator*=(const mat4 input);
		vec3 multiply(const vec3& input) const;
		vec4 multiply(const vec4& input) const;
		friend vec3 operator*(const mat4& left, const vec3& right);
		friend vec4 operator*(const mat4& left, const vec4& right);

		mat4& invert();
	};
} }
 // !MAT4_H
