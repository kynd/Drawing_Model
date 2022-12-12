#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform sampler2DRect original;
uniform vec4 color;


void main() {
    vec4 oSamp = texture(original, texCoordVarying.xy);
    vec4 bSamp = texture(tex, texCoordVarying.xy);
    vec4 color = mix(oSamp, color, bSamp.a);
    FragColor = color;
}
