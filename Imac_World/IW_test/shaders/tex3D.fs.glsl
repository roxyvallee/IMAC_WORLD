#version 330 core

in vec3 vPosition_vs; 
in vec3 vNormal_vs;
in vec2 vTexCoords; 
	
out vec3 fFragColor;

uniform sampler2D uGrassTexture;

void main() {
	fFragColor = texture(uGrassTexture, vTexCoords).xyz;
	//fFragColor = vec3(0.52, 0.39, 0.39);
}
		