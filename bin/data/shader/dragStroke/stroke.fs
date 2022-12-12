#version 150

uniform float frame;
uniform sampler2DRect buffer;
uniform sampler2DRect map;
uniform vec3 p0;
uniform vec3 p1;
out vec4 FragColor;
in vec2 texCoordVarying;


void main() {
    vec2 px = gl_FragCoord.xy;
    float d0 = length(p0.xy - px);
    float d1 = length(p1.xy - px);
    float t = d0 / (d0 + d1);
    vec4 color = texture(map, vec2(t * 512, 0.5));
    FragColor = color;
}
