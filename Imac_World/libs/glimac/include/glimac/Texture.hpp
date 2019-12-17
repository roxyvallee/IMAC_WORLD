#ifndef _TEXTURE_HPP 
#define _TEXTURE_HPP

#pragma once
#include <string>
#include <iostream>
#include <glimac/Image.hpp>
#include <GL/glew.h>

namespace glimac
{
	class Texture
	{
		private:
			std::string m_name;
			std::unique_ptr<Image> m_texturePointer;

		public:
			Texture(){};
			Texture(std::string texture);
			GLuint m_textureId;
			inline GLuint getID() const{ return m_textureId;}
	};
}

#endif 