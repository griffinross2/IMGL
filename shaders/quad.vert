#version 450 core

// A line defining one of the diagonals
layout (location = 0) in vec2 aPos;

void main()
{
	gl_Position = vec4(aPos, 0.0, 1.0);
}