#include <string>
#include <iostream>
#include "glimac/Texture.hpp"
#include <GL/glew.h>

namespace glimac {
	Texture::Texture(std::string texture) {
		m_name = texture;
		m_texturePointer = loadImage("../assets/textures/" + m_name + ".jpg");
		if(m_texturePointer == NULL)
		{
			std::cerr << "Couldn't load texture" << m_texturePointer << std::endl;
		}
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexImage2D(GL_TEXTURE_2D,  0,  GL_RGBA,  m_texturePointer->getWidth(),  m_texturePointer->getHeight(),  0,  GL_RGBA,  GL_FLOAT,  m_texturePointer->getPixels());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D,  0);
    }
}
