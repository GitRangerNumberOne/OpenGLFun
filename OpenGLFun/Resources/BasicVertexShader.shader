#version 460 core
layout(location = 0) in vec3 a_Position;
out vec3 position;
void main()
{
	gl_Position = a_Position;
	position = a_Position;
}