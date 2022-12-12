#version 150
#define PI 3.14159265359
#define N 32
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect prev;
uniform sampler2DRect base;
uniform sampler2DRect blur;
uniform sampler2DRect original;
uniform sampler2DRect noise;
uniform vec2 dir;
uniform vec2 pos;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

void main() {
    vec4 noiseSamp = texture(noise, texCoordVarying.xy + pos.xy);
    vec4 prevSamp = texture(prev, texCoordVarying.xy);
    vec4 baseSamp = texture(base, texCoordVarying.xy);
    vec4 blurSamp = texture(blur, texCoordVarying.xy);

    vec2 offCoord = texCoordVarying.xy + noiseSamp.xy * 24.0;
    vec4 oSamp = texture(prev, offCoord);
    vec4 bSamp = texture(base, offCoord);
    float lev = max(0.0, min(baseSamp.a, 0.5 - blurSamp.a * 0.3));
    

    //vec4 mixColor = mix(baseSamp, oSamp, blurSamp.a * 0.5);
    vec4 color = mix(prevSamp, baseSamp, lev);
    color.a = 1.0;
    //sssqcolor = mix(prevSamp, baseSamp, lev);

    float lev2 = (min(oSamp.a, baseSamp.a));
    float lev3 = random(texCoordVarying.xy) - noiseSamp.b;
    color = mix(color, oSamp, clamp(lev2 * lev3, 0.0, 1.0));
    //color = prevSamp;
    FragColor = color;
}
