#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 col;

in Data
{
	vec4 position;
	vec4 color;
} fs_in;

void main()
{
	color = fs_in.color;
}