#version 150
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect tex;
uniform sampler2DRect canvasCopy;
uniform vec4 bounds;

uniform vec4 colorA;
uniform vec4 colorB;
uniform vec2 dir;
uniform vec2 center;
uniform float breadth;
uniform int isRadial;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

float srand(vec2 st) {
    return random(st) - random(st+vec2(1.234,3.452));
}

void main() {
    vec2 crd = texCoordVarying.xy;
    vec4 oSamp = texture(canvasCopy, crd);

    float t;
    if (isRadial == 0) {
        vec2 uv = crd / bounds.zw - vec2(0.5);
        t = dot(uv, normalize(dir)) + center.x;
    } else {
        float diag = sqrt(bounds.z * bounds.z + bounds.w * bounds.w);
        t = length(crd - center * bounds.zw) / diag * 2.0;
    }

    float f = (t - 0.5) * 2.0;
    float h = sqrt(1.0 - pow(f, 2.0));

    vec3 norm = normalize(vec3(dir * f, 1.0));
    float l = dot(norm, normalize(vec3(1.0)));
    l += pow(dot(norm, normalize(vec3(0.0, 0.0, 1.0))), 16.0);
    //vec2 rc = vec2(srand(crd), srand(crd + vec2(0.12, 0.34)));
    //vec2 rCoord = vec2(ivec2((crd.xy + rc * 1) / 4)) * 0.01;
    vec4 samp = texture(tex, crd.xy);
    vec4 outCol = mix(colorA, colorB, 
        smoothstep(0.5 - breadth * 0.5, 0.5 + breadth * 0.5,
        t));
    outCol.rgb *= l;
    outCol = mix(oSamp, outCol, samp.a);
    FragColor = outCol;
}

