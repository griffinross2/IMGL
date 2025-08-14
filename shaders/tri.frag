#version 450 core

in vec4 vecColor;
out vec4 FragColor;

void main()
{
	// Apply a simple color with alpha
    FragColor = vecColor;
}