#version 460 core

in vec3 position;

void main()
{
	color = vec4(position, 1.0);
}