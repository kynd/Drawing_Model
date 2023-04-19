#version 150
#define PI 3.14159265359
#define N 32
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect prev;
uniform sampler2DRect base;
uniform sampler2DRect canvasCopy;
uniform vec4 colorA;
uniform vec4 colorB;
uniform vec2 dir;
uniform vec2 res;
uniform vec4 bounds;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}


float srand(vec2 st) {
    return random(st) - random(st+vec2(1.234,3.452));
}

vec2 constrainCoord(vec2 crd) {
    return clamp(bounds.xy + crd.xy + vec2(1.0, 1.0), vec2(2.0), vec2(res) - vec2(2.0)) - bounds.xy;
}

void main() {
    vec2 crd = texCoordVarying.xy;
    vec4 originalSamp = texture(canvasCopy, crd);
    vec4 baseSamp = texture(base, crd);
    vec4 prevSamp = texture(prev, crd);


    vec2 perpDir = vec2(dir.y, -dir.x);
    vec2 uv = crd / bounds.zw - vec2(0.5);
    float t = dot(uv, normalize(perpDir)) + 0.5;


    vec4 mixedColor = mix(colorA, colorB, smoothstep(0.25, 0.75, t));
    vec2 offCoord = crd;
    float d = 1.0;
    for (int i = 0; i < 8; i ++) {
        offCoord +=  dir * d;
        d *= 1.5;
        vec4 offBaseSamp = texture(base, constrainCoord(offCoord));
        vec4 prevBleedSamp = texture(prev, constrainCoord(offCoord));
        mixedColor = mix(mixedColor, prevBleedSamp, 0.9 * offBaseSamp.a);
    }

    vec4 outCol = mix(originalSamp, mixedColor, baseSamp.a);

    FragColor = outCol;
}