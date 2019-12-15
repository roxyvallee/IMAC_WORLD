#version 330

uniform mat3 uModelMatrix;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexUV;

out vec2 vFragUV;
//out vec3 vPosition;



void main() {

	
	vFragUV = aVertexUV;
	//mat3 M = rotate(uTime);
	gl_Position = vec4(uModelMatrix * vec3(aVertexPosition,1),1);
	//vPosition = gl_Position.xyz;
	//gl_Position = vec4((M* vec3(aVertexPosition, 1)).xy, 0, 1);
	//gl_Position = vec4(aVertexPosition, 0, 1);
}