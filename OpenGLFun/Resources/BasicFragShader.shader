#version 460 core

out vec4 color;
in vec3 position;

void main()
{
	color = vec4(position, 1.0);
}