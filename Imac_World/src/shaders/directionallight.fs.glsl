#version 330

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform vec3 uCubeColor;

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

// lumière ambiante
uniform float uAmbiantLightIntensity;

uniform sampler2D uTexture;

vec3 blinnPhong() {
  // Couleur=Li(Kd(wi˙N)+Ks(halfVector˙N)shininess)
  vec3 wi = normalize(uLightDir_vs);
  vec3 halfVector = normalize(-vPosition_vs);
  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);
  vec3 color = uLightIntensity*(p1+p2+uAmbiantLightIntensity);
  return color;
}

void main() {
  //fFragColor = blinnPhong() * texture(uTexture, vTexCoords).xyz;
  fFragColor = blinnPhong() * texture(uTexture, vTexCoords).xyz * uCubeColor;
}