#version 150

uniform sampler2DRect localCanvas;
uniform sampler2DRect canvas;
uniform sampler2DRect mask;

out vec4 FragColor;
in vec2 texCoordVarying;

void main() {
    vec4 lcSamp = texture(localCanvas, texCoordVarying.xy);
    vec4 cSamp = texture(canvas, texCoordVarying.xy);
    vec4 mSamp = texture(mask, texCoordVarying.xy);

    vec4 outCol = mix(cSamp, lcSamp, mSamp.r);
    FragColor = outCol;
}
