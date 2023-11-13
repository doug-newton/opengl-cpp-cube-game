#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec4 vertex_colour;
layout (location = 2) in vec2 vertex_tex_coord;

uniform mat4 model;

out vec4 colour;
out vec2 tex_coord;

void main() {
    colour = vertex_colour;
    tex_coord = vertex_tex_coord;
    gl_Position = model * vec4(vertex_position.xyz, 1.0);
}