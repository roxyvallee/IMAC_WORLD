#version 330 core

uniform vec3 uColor;
uniform sampler2D uTexture;

in vec2 vFragUV;
//in vec3 vPosition;
out vec3 fFragColor;


void main() {
    //fFragColor = vec3(0,1,0);
    //fFragColor = vPosition; couleur d'après position
    vec4 textureColor = texture(uTexture, vFragUV);
    //fFragColor = uColor;
    fFragColor = textureColor.xyz;
}