#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 projection;

out vec4 vecColor;

void main()
{
	gl_Position = projection * vec4(aPos, 1.0);
	vecColor = aColor;
}