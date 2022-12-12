#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform vec4 color;


void main() {
    vec4 samp = texture(tex, texCoordVarying.xy);
    vec4 outCol = mix(vec4(0.0), color, samp.r);
    FragColor = outCol;
}
