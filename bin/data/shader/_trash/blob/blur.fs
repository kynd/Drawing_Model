#version 150
#define PI 3.14159265359
#define N 12
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

    FragColor = color;
}
