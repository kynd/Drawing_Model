#version 150
#define PI 3.14159265359
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform vec4 colorA;
uniform vec4 colorB;
uniform float freq;


void main() {
    float l = sin(texCoordVarying.x * freq * PI);
    FragColor = vec4(vec3(l), 1.0);
}
