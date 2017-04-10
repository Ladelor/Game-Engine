#include "mat4.h"

namespace NumberOne { namespace Math{

	mat4::mat4()
	{
		for (int i = 0; i < MATRICE_SIZE * MATRICE_SIZE; i++)
			elements[i] = 0.0f;
	}

	mat4::mat4(float diag) : mat4()
	{
		for (int i = 0; i < MATRICE_SIZE; i++)
			elements[i + i * MATRICE_SIZE] = diag;
	}

	std::ostream& operator<<(std::ostream& stream, const mat4& mat4)
	{
		stream << "mat4: ";
		for (int col = 0; col < MATRICE_SIZE; col++)
		{
			for (int row = 0; row < MATRICE_SIZE; row++)
			{
				stream << mat4.elements[row + col * MATRICE_SIZE] << " ";
			}
			stream << std::endl << "      ";
		}
		return stream;
	}

	float mat4::degsToRads(const float degress)
	{
		return degress * (M_PI / 180);
	}

	vec4 mat4::getColumn(int column)
	{
		column *= 4;
		return vec4(elements[column], elements[column + 1], elements[column + 2], elements[column + 3]);
	}

	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}
	
	mat4 mat4::orthographic(float l, float r, float bot, float top, float near, float far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * MATRICE_SIZE] = 2.0f / (r - l);
		result.elements[1 + 1 * MATRICE_SIZE] = 2.0f / (top - bot);
		result.elements[2 + 2 * MATRICE_SIZE] = 2.0f / (near - far);
		result.elements[0 + 3 * MATRICE_SIZE] = (l + r) / (l - r);
		result.elements[1 + 3 * MATRICE_SIZE] = (top + bot) / (bot - top);
		result.elements[2 + 3 * MATRICE_SIZE] = (far + near) / (far - near);

		return result;
	}

	mat4 mat4::perspective(float fov, float aspRatio, float near, float far)
	{
		mat4 result;

		float x = tan(degsToRads(fov / 2));
		result.elements[0 + 0 * MATRICE_SIZE] = 1.0f / (aspRatio * x);
		result.elements[1 + 1 * MATRICE_SIZE] = 1.0f / x;
		result.elements[2 + 2 * MATRICE_SIZE] = (far + near)/(far - near);
		result.elements[2 + 3 * MATRICE_SIZE] = (2.0f * far * near)/(far - near);
		result.elements[3 + 2 * MATRICE_SIZE] = -1.0f;

		return result;
	}

	mat4 mat4::translation(const vec3& translation)
	{
		mat4 result(1.0f);
		
		result.elements[0 + 3 * MATRICE_SIZE] = translation.x;
		result.elements[1 + 3 * MATRICE_SIZE] = translation.y;
		result.elements[2 + 3 * MATRICE_SIZE] = translation.z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis)
	{
		mat4 result(1.0f);

		float angleRads = degsToRads(angle);
		float c = cos(angleRads), s = sin(angleRads);
		float oneMC = 1.0f - c;
		float x = axis.x, y = axis.y, z = axis.z;

		result.elements[0 + 0 * MATRICE_SIZE] = x * oneMC + c;
		result.elements[1 + 0 * MATRICE_SIZE] = y * x * oneMC + z * s;
		result.elements[2 + 0 * MATRICE_SIZE] = x * z * oneMC - y * s;

		result.elements[0 + 1 * MATRICE_SIZE] = x * y * oneMC - z * s;
		result.elements[1 + 1 * MATRICE_SIZE] = y * oneMC + c;
		result.elements[2 + 1 * MATRICE_SIZE] = y * z * oneMC + x * s;

		result.elements[0 + 2 * MATRICE_SIZE] = x * z * oneMC + y * s;
		result.elements[1 + 2 * MATRICE_SIZE] = y * z * oneMC - x * c;
		result.elements[2 + 2 * MATRICE_SIZE] = z * oneMC + c;

		return result;
	}

	mat4 mat4::scale(const vec3& scale)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * MATRICE_SIZE] = scale.x;
		result.elements[1 + 1 * MATRICE_SIZE] = scale.y;
		result.elements[2 + 2 * MATRICE_SIZE] = scale.z;

		return result;
	}

	mat4& mat4::multiply(const mat4& input)
	{
		float temp[16];
		for (int col = 0; col < MATRICE_SIZE; col++)
		{
			for (int row = 0; row < MATRICE_SIZE; row++)
			{
				float product = 0.0f;
				for (int ele = 0; ele < MATRICE_SIZE; ele++)
				{
					product += elements[row + ele * MATRICE_SIZE] * input.elements[ele + col * MATRICE_SIZE];
				}
				temp[row + col * MATRICE_SIZE] = product;
			}
		}
		memcpy(elements, temp, 4 * 4 * sizeof(float));
		return *this;
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return (left.multiply(right));
	}

	mat4& mat4::operator*=(const mat4 input)
	{
		return this->multiply(input);
	}


	vec3 mat4::multiply(const vec3& input) const
	{
		return vec3(
			elements[MATRICE_SIZE * 0 + 0] * input.x + elements[MATRICE_SIZE * 1 + 0] * input.y + elements[MATRICE_SIZE * 2 + 0] * input.z + elements[MATRICE_SIZE * 3 + 0],
			elements[MATRICE_SIZE * 0 + 1] * input.x + elements[MATRICE_SIZE * 1 + 1] * input.y + elements[MATRICE_SIZE * 2 + 1] * input.z + elements[MATRICE_SIZE * 3 + 1],
			elements[MATRICE_SIZE * 0 + 2] * input.x + elements[MATRICE_SIZE * 1 + 2] * input.y + elements[MATRICE_SIZE * 2 + 2] * input.z + elements[MATRICE_SIZE * 3 + 2]
		);
	}

	vec4 mat4::multiply(const vec4& input) const
	{
		return vec4(
			elements[MATRICE_SIZE * 0 + 0] * input.x + elements[MATRICE_SIZE * 1 + 0] * input.y + elements[MATRICE_SIZE * 2 + 0] * input.z + elements[MATRICE_SIZE * 3 + 0] * input.w,
			elements[MATRICE_SIZE * 0 + 1] * input.x + elements[MATRICE_SIZE * 1 + 1] * input.y + elements[MATRICE_SIZE * 2 + 1] * input.z + elements[MATRICE_SIZE * 3 + 1] * input.w,
			elements[MATRICE_SIZE * 0 + 2] * input.x + elements[MATRICE_SIZE * 1 + 2] * input.y + elements[MATRICE_SIZE * 2 + 2] * input.z + elements[MATRICE_SIZE * 3 + 2] * input.w,
			elements[MATRICE_SIZE * 0 + 3] * input.x + elements[MATRICE_SIZE * 1 + 3] * input.y + elements[MATRICE_SIZE * 2 + 3] * input.z + elements[MATRICE_SIZE * 3 + 3] * input.w
		);
	}

	vec3 operator*(const mat4& left, const vec3& right)
	{
		return left.multiply(right);
	}

	vec4 operator*(const mat4& left, const vec4& right)
	{
		return left.multiply(right);
	}

	mat4& mat4::invert()
		 {
		double temp[16];
		
		temp[0] = elements[5] * elements[10] * elements[15] -
		elements[5] * elements[11] * elements[14] -
		elements[9] * elements[6] * elements[15] +
		elements[9] * elements[7] * elements[14] +
		elements[13] * elements[6] * elements[11] -
		elements[13] * elements[7] * elements[10];
		
		temp[4] = -elements[4] * elements[10] * elements[15] +
		elements[4] * elements[11] * elements[14] +
		elements[8] * elements[6] * elements[15] -
		elements[8] * elements[7] * elements[14] -
		elements[12] * elements[6] * elements[11] +
		elements[12] * elements[7] * elements[10];
		
		temp[8] = elements[4] * elements[9] * elements[15] -
		elements[4] * elements[11] * elements[13] -
		elements[8] * elements[5] * elements[15] +
		elements[8] * elements[7] * elements[13] +
		elements[12] * elements[5] * elements[11] -
		elements[12] * elements[7] * elements[9];
		
		temp[12] = -elements[4] * elements[9] * elements[14] +
		elements[4] * elements[10] * elements[13] +
		elements[8] * elements[5] * elements[14] -
		elements[8] * elements[6] * elements[13] -
		elements[12] * elements[5] * elements[10] +
		elements[12] * elements[6] * elements[9];
		
		temp[1] = -elements[1] * elements[10] * elements[15] +
		elements[1] * elements[11] * elements[14] +
		elements[9] * elements[2] * elements[15] -
		elements[9] * elements[3] * elements[14] -
		elements[13] * elements[2] * elements[11] +
		elements[13] * elements[3] * elements[10];
		
		temp[5] = elements[0] * elements[10] * elements[15] -
		elements[0] * elements[11] * elements[14] -
		elements[8] * elements[2] * elements[15] +
		elements[8] * elements[3] * elements[14] +
		elements[12] * elements[2] * elements[11] -
		elements[12] * elements[3] * elements[10];
		
		temp[9] = -elements[0] * elements[9] * elements[15] +
		elements[0] * elements[11] * elements[13] +
		elements[8] * elements[1] * elements[15] -
		elements[8] * elements[3] * elements[13] -
		elements[12] * elements[1] * elements[11] +
		elements[12] * elements[3] * elements[9];
		
		temp[13] = elements[0] * elements[9] * elements[14] -
		elements[0] * elements[10] * elements[13] -
		elements[8] * elements[1] * elements[14] +
		elements[8] * elements[2] * elements[13] +
		elements[12] * elements[1] * elements[10] -
		elements[12] * elements[2] * elements[9];
		
		temp[2] = elements[1] * elements[6] * elements[15] -
		elements[1] * elements[7] * elements[14] -
		elements[5] * elements[2] * elements[15] +
		elements[5] * elements[3] * elements[14] +
		elements[13] * elements[2] * elements[7] -
		elements[13] * elements[3] * elements[6];
		
		temp[6] = -elements[0] * elements[6] * elements[15] +
		elements[0] * elements[7] * elements[14] +
		elements[4] * elements[2] * elements[15] -
		elements[4] * elements[3] * elements[14] -
		elements[12] * elements[2] * elements[7] +
		elements[12] * elements[3] * elements[6];
		
		temp[10] = elements[0] * elements[5] * elements[15] -
		elements[0] * elements[7] * elements[13] -
		elements[4] * elements[1] * elements[15] +
		elements[4] * elements[3] * elements[13] +
		elements[12] * elements[1] * elements[7] -
		elements[12] * elements[3] * elements[5];
		
		temp[14] = -elements[0] * elements[5] * elements[14] +
		elements[0] * elements[6] * elements[13] +
		elements[4] * elements[1] * elements[14] -
		elements[4] * elements[2] * elements[13] -
		elements[12] * elements[1] * elements[6] +
		elements[12] * elements[2] * elements[5];
		
		temp[3] = -elements[1] * elements[6] * elements[11] +
		elements[1] * elements[7] * elements[10] +
		elements[5] * elements[2] * elements[11] -
		elements[5] * elements[3] * elements[10] -
		elements[9] * elements[2] * elements[7] +
		elements[9] * elements[3] * elements[6];
		
		temp[7] = elements[0] * elements[6] * elements[11] -
		elements[0] * elements[7] * elements[10] -
		elements[4] * elements[2] * elements[11] +
		elements[4] * elements[3] * elements[10] +
		elements[8] * elements[2] * elements[7] -
		elements[8] * elements[3] * elements[6];
		
		temp[11] = -elements[0] * elements[5] * elements[11] +
		elements[0] * elements[7] * elements[9] +
		elements[4] * elements[1] * elements[11] -
		elements[4] * elements[3] * elements[9] -
		elements[8] * elements[1] * elements[7] +
		elements[8] * elements[3] * elements[5];
		
		temp[15] = elements[0] * elements[5] * elements[10] -
		elements[0] * elements[6] * elements[9] -
		elements[4] * elements[1] * elements[10] +
		elements[4] * elements[2] * elements[9] +
		elements[8] * elements[1] * elements[6] -
		elements[8] * elements[2] * elements[5];
		
		double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
		determinant = 1.0 / determinant;
		
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = temp[i] * determinant;
		
		return *this;
		}
	
} }