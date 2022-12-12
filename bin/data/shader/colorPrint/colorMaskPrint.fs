#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform vec4 keyColor;


void main() {
    vec4 samp = texture(tex, texCoordVarying.xy);
    float d = 1.0 - smoothstep(0.5, 0.51, distance(keyColor, samp));
    vec4 outCol = mix(vec4(0.0), vec4(1.0), d);
    FragColor = outCol;
}
