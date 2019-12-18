#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTextCoords;

uniform vec3 uCubeColor;

out vec3 fFragColor;

void main()
{
	/*if(vcubeColor == 1) fFragColor = vec3(1.f, 0.f, 0.f); 
	if(vcubeColor == 2) fFragColor = vec3(0.f, 1.f, 0.f); 
	if(vcubeColor == 3) fFragColor = vec3(0.f, 0.f, 1.f); */
	//fFragColor = vec3(0.f, 1.f, 0.f);
	fFragColor = uCubeColor;
	//fFragColor = vec3(normalize(vNormal_vs));
}
