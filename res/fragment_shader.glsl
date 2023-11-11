#version 330 core

in vec4 colour;
in vec2 tex_coord;

uniform float opacity = 1;
uniform sampler2D current_texture;

out vec4 frag_colour;

void main() {
    frag_colour = vec4(texture(current_texture, tex_coord).rgb, opacity);
}