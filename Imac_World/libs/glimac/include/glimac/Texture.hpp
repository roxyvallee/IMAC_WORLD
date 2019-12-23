#ifndef _TEXTURE_HPP__
#define _TEXTURE_HPP__

#include <iostream>
#include <string>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <GL/glew.h>

namespace glimac
{
	class Texture
	{
		private:
			//std::string m_name;
			GLuint m_textureId;
			std::unique_ptr<Image> m_texturePointer;

		public:
			// Constructors
			Texture(){};
			Texture(const FilePath& filepath);
			inline GLuint getId() const{return m_textureId;}

	};
}

#endif 