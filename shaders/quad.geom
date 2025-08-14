#version 450 core

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

// Generate a quad with the line endpoints as opposite corners
void main() {
    vec2 p0 = gl_in[0].gl_Position.xy;
    vec2 p1 = gl_in[1].gl_Position.xy;

    // Emit the vertices for the quad
    gl_Position = projection * vec4(p0.x, p1.y, 0.0, 1.0);
    EmitVertex();
    gl_Position = projection * vec4(p0, 0.0, 1.0);
    EmitVertex();
    gl_Position = projection * vec4(p1, 0.0, 1.0);
    EmitVertex();
    gl_Position = projection * vec4(p1.x, p0.y, 0.0, 1.0);
    EmitVertex();

    EndPrimitive();
}