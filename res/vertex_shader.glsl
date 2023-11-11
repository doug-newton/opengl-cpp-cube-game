#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec4 vertex_colour;
layout (location = 2) in vec2 vertex_tex_coord;

out vec4 colour;
out vec2 tex_coord;

void main() {
    colour = vertex_colour;
    tex_coord = vertex_tex_coord;
    gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
}