#version 330

// Shader inputs
in vec3 vPosition_vs; // Position of the transformed vertex in the View space
in vec3 vNormal_vs; // Normal of the transformed top in the View space
in vec2 vTexCoords; // Vertex texture coordinates

uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

// directional light
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensityD;

// point of light
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensityP;

// surrounding light
uniform float uAmbiantLightIntensity;

out vec3 fFragColor;

vec3 blinnPhongD() {

  vec3 w_zero = normalize(-vPosition_vs);
  vec3 wi = normalize(-uLightDir_vs);
  vec3 halfVector = (w_zero + wi)/2;

  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);
  vec3 lightD = uLightIntensityD*(p1+p2);

  return lightD;
}

vec3 blinnPhongP() {
	float d = distance(uLightPos_vs, vPosition_vs);
  vec3 w_zero = normalize(-vPosition_vs);
  vec3 wi = normalize(uLightPos_vs - vPosition_vs);
  vec3 halfVector = (w_zero + wi)/2;

  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);
  vec3 lightP = (uLightIntensityP / (d*d)) *(p1+p2);

  return lightP;
}

void main() {
	vec3 finalLight = min(blinnPhongD() + blinnPhongP() + uAmbiantLightIntensity, 1.);
  fFragColor = finalLight * texture(uTexture, vTexCoords).xyz;
}
