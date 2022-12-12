#version 150

uniform float frame;
uniform sampler2DRect prev;
uniform sampler2DRect canvas;
uniform sampler2DRect noiseBuffer;
uniform int isFirstFrame;
uniform vec3 p0;
uniform vec3 p1;
uniform vec4 cbl;
uniform vec4 cbr;
uniform vec4 cel;
uniform vec4 cer;
uniform vec4 bg;
uniform float pos;

out vec4 FragColor;
in vec2 texCoordVarying;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

void main() {

    vec2 px = gl_FragCoord.xy;
    float t = px.x / 1024;
    
    float t2 = fract(t * 2.0);

    vec3 p = mix(p0, p1, t);
    
    vec4 nSamp = texture(noiseBuffer, p.xy);
    vec4 cSamp = texture(canvas, p.xy + nSamp.xy * 10.0);
    
    vec4 b = mix(cbl, cbr, t2);
    vec4 e = mix(cel, cer, t2);

    float mixAmt = abs(nSamp.b);

    vec4 paint = mix(b, e, pos);//pos);
    vec4 color;
    vec2 coord = texCoordVarying + nSamp.xy * 0.2;
    if (isFirstFrame != 0) {
        color = paint;
    } else {
        vec4 pSamp = texture(prev, coord);
        if (length(cSamp.rgb - vec3(bg)) < 0.1) {
            color = mix(pSamp, cSamp, 0.0000015 * mixAmt);
            //color = mix(pSamp, paint, 0.025);
        } else {
            color = mix(pSamp, cSamp, 0.05 * mixAmt);
        }
    }

   color.a = min(1.0, color.a * 1.0);// * (0.9 + random(texCoordVarying) * 0.1);
   float dToEdge = min(coord.x, 1024 - coord.x);
   //color.a = smoothstep(0.3, 0.6, min(color.a, dToEdge * 0.01));
 FragColor = color;
}
