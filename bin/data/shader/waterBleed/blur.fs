#version 150
#define PI 3.14159265359
#define N 32
out vec4 FragColor;
in vec2 texCoordVarying;

uniform sampler2DRect base;
uniform vec2 dir;


void main() {

    vec4 sum = vec4(0.0);
    float wSum = 0.0;
    for (int i = -N; i <= N; i ++) {
        float w = float(N + 1 - abs(i)) / (N + 1);
        vec4 samp = texture(base, texCoordVarying.xy + dir * i);
        sum += samp * w;
        wSum += w;
    }
    vec4 color = sum / wSum;
    color = vec4(vec3(1.0), color.a);
    FragColor = color;
}
