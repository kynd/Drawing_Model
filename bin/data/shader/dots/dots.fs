#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform sampler2DRect canvasCopy;
uniform vec4 colorA;
uniform vec4 colorB;
uniform vec2 dir;
uniform vec4 bounds;

vec2 rotate2d(vec2 v, float _angle){
    return v * mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

void main() {
    float size = length(dir) * 8.0;
    float ang = atan(dir.y, dir.x);
    vec2 coord = rotate2d(texCoordVarying.xy, ang);
    vec2 lCoord = fract(coord / size);
    vec2 iCoord = vec2(ivec2(coord / size)) * size;
    iCoord = rotate2d(iCoord, -ang);
    vec4 oSamp = texture(canvasCopy, texCoordVarying.xy);
    vec4 tSamp = texture(tex, iCoord);
    float d = smoothstep(0.0, 1.0 / (size + 0.1), 0.5 - distance(lCoord, vec2(0.5)));
    vec4 outCol = mix(oSamp, colorA, d * tSamp.a);
    FragColor = outCol;
}

