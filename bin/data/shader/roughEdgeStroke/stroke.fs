#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform vec4 color;


void main() {
    FragColor = color;
}
