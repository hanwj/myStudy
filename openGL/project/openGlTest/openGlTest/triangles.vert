#version 430 core

lauout(location = 0) in vec4 vPosition
void main()
{
	gl_Position = vPosition;
}