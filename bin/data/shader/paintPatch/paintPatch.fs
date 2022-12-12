#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform sampler2DRect canvasCopy;
uniform sampler2DRect noise;
uniform vec4 colorA;
uniform vec4 colorB;
uniform vec2 dir;
uniform vec4 bounds;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

float srand(vec2 st) {
    return random(st) - random(st+vec2(1.234,3.452));
}

void main() {
    vec2 crd = texCoordVarying.xy;
    vec4 oSamp = texture(canvasCopy, crd);
    vec4 nSamp = texture(noise, crd + bounds.xy);
    vec2 uv = crd / bounds.zw - nSamp.rg * 0.1;

    float diag = sqrt(bounds.z * bounds.z + bounds.w * bounds.w);
    vec2 sDir = normalize(vec2(dir.y, -dir.x) + nSamp.rg);
    float t = sin(dot(uv, sDir) * diag * 2.0/ (5.0 + nSamp.b * 4.0));

    vec2 rc = vec2(srand(crd), srand(crd + vec2(0.12, 0.34)));
    vec2 rCoord = vec2(ivec2((crd.xy + rc * 1) / 4)) * 0.5;
    vec4 samp = texture(tex, crd.xy);
    float lev =  t + srand(rCoord);
    vec4 outCol = mix(colorA, colorB, smoothstep(0.25, 0.5, lev));
    //outCol = nSamp;
    outCol = mix(oSamp, outCol, samp.a);
    FragColor = outCol;
}

