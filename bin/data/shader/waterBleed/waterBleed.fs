#version 150
#define PI 3.14159265359
#define N 32
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect prev;
uniform sampler2DRect base;
uniform sampler2DRect canvasCopy;
uniform sampler2DRect blur;
uniform sampler2DRect noise;
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
    vec4 noiseSamp = texture(noise, crd + bounds.xy);
    vec4 prevSamp = texture(prev, crd);
    //vec4 baseSamp = texture(base, crd);
    //vec4 blurSamp = texture(blur, crd);

    vec4 offBlurSamp = texture(blur, crd + noiseSamp.xy * 8.0);
    vec4 offBaseSamp = texture(base, crd);
    vec2 offCoord = crd + noiseSamp.xy * 4.0 * offBlurSamp.a;
    vec4 prevBleedSamp = texture(prev, constrainCoord(offCoord));

    // Gradient
    vec2 uv = crd / bounds.zw - vec2(0.5);
    float t = dot(uv, normalize(dir)) + 0.5;
    vec2 rc = vec2(srand(crd), srand(crd + vec2(0.12, 0.34)));
    vec2 rCoord = vec2(ivec2((crd.xy + rc * 1) / 4)) * 0.01;
    vec4 gradCol = mix(colorA, colorB, smoothstep(0.1, 0.9, t + srand(rCoord) * 0.3));

    // Water Color Mix
    //vec4 mixed = (vec4(1.0) - gradCol * prevBleedSamp;
    //mixed.a = 1.0;
    vec4 mixed = mix(max(gradCol, prevBleedSamp), gradCol * prevBleedSamp, 0.9);
    //mixed = mix(gradCol, mixed, 0.5);

    //gradCol = mix(gradCol, mixed, 1.0);
    float mixLev = max(0.0, min(offBaseSamp.a, 0.5 - offBlurSamp.a * 0.3));
    mixLev = clamp(mixLev - noiseSamp.b * 0.1, 0.0, 1.0);
    vec4 mixColor = mix(prevBleedSamp, mixed, mixLev * 0.5);

    vec4 outCol = mix(prevSamp, mixColor, offBaseSamp.a);
    FragColor = outCol;
}