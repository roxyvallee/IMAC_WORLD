#pragma once

#include <glm/glm.hpp>

namespace glimac{

	class ShapeGrid
	{
	private:
		int m_coordX;
		int m_coordY;
		int m_coordZ;
		int m_type;
		glm::vec3 m_color;
		
	public:
		//ShapeGrid(){};
		ShapeGrid(int coordX, int coordY, int coordZ, glm::vec3 color)
		:m_coordX(coordX), m_coordY(coordY), m_coordZ(coordZ), m_type(0), m_color(color){}

		inline int get_CoordX() const { return m_coordX; }

		inline int get_CoordY() const { return m_coordY; }

		inline int get_CoordZ() const { return m_coordZ; }

		inline int get_Type() const { return m_type; }

		inline glm::vec3 get_Color() { return m_color; }

		inline glm::vec3* get_ColorPtr() { return &m_color; }

		inline void set_Color(const glm::vec3 color) { m_color = color; }

		inline void set_Type(const int type) { m_type = type; }
	};
}