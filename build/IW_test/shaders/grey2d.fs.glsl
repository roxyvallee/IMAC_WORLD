#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
	float alpha = 5;
	float beta = 15;
	float a = alpha * exp(-beta * distance( vec2(0,0), vFragPosition));
	float M = (vFragColor.r + vFragColor.g + vFragColor.b) / 3;
	
	float b = length(fract(5.0 * vFragPosition)); // motif carré
	float c = length(abs(fract(5.0 * vFragPosition) * 2.0 - 1.0)); // motif ruche
	float d = mod(floor(10.0 * vFragPosition.x) + floor(10.0*vFragPosition.y), 2.0); // motif damier
	float e = smoothstep(0.3, 0.32, length(fract(5.0*vFragPosition)- 0.5)); // motif pois
	float f = smoothstep(0.4, 0.5, max(abs(fract(8.0 * vFragPosition.x - 0.5 * mod(floor(8.0 * vFragPosition.y), 2.0)) - 0.5), abs(fract(8.0 * vFragPosition.y)- 0.5))); // motif brique
  	fFragColor = f * vFragColor;
  	// fFragColor = vec3(M,M,M); grey

};