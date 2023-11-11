#version 330 core

in vec4 colour;
out vec4 frag_colour;
uniform float opacity = 1;

void main() {
    frag_colour = vec4(colour.xyz, opacity);
}