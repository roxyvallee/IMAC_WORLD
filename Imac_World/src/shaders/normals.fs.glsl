#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTextCoords;

uniform vec3 uCubeColor;

out vec3 fFragColor;

void main()
{
	fFragColor = uCubeColor;
	//fFragColor = vec3(normalize(vNormal_vs));
}
