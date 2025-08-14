#version 450 core

uniform vec4 color;
out vec4 FragColor;

void main()
{
	// Apply a simple color with alpha
    FragColor = color;
}