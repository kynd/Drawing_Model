#version 150

uniform mat4 modelViewProjectionMatrix;
uniform mat4 textureMatrix;

in vec4 position;
in vec2 texcoord;
in vec4 normal;

out vec2 texCoordVarying;
out vec4 normalVarying;

void main(){
  texCoordVarying = texcoord;
  normalVarying = normal;
	gl_Position = modelViewProjectionMatrix * position;
}
