#version 150
#pragma include "../common/noise.incl"
#define PI 3.14159265359

out vec4 FragColor;
in vec2 texCoordVarying;

uniform vec2 res;
uniform float time;

vec3 layeredNoise(vec2 v) {
    int iter = 3;
    float amt = 1.0, scl = 50.0;

    vec3 n = vec3(0.0);
    float amtSum = 0.0;
    for (int i = 0; i < iter; i ++) {
        n += v3n3(vec3(v * scl, time * 100.0 )) * amt;
        n -= v3n3(vec3(v * scl, time * 100.0 + 1000.0)) * amt;
        scl *= 5.5;
        amtSum += amt;
        amt *= 0.5;
    }
    return n / amtSum;
}

float nStep(float n) {
    return float(int(n * 4.0)) / 4.0;
}

void main() {
    float minSide = min(res.x, res.y);
    vec2 coord = texCoordVarying / minSide;
    vec3 c = layeredNoise(coord);
    vec4 color = vec4(c, 1.0);
    /*
    color.r = nStep(color.r);
    color.g = nStep(color.g);
    color.b = nStep(color.b);
    */
    FragColor = color;
}
