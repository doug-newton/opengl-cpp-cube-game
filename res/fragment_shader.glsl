#version 330 core

in vec4 colour;
in vec2 tex_coord;

uniform float opacity = 1;
uniform float mix_amount = 0.5;

uniform sampler2D texture_slot0;
uniform sampler2D texture_slot1;

out vec4 frag_colour;

void main() {
    frag_colour = mix(texture(texture_slot0, tex_coord), texture(texture_slot1, tex_coord), mix_amount);
}