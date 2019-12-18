#pragma once

namespace glimac{

	class ShapeGrid
	{
	private:
		int m_coordX;
		int m_coordY;
		int m_coordZ;
		
	public:
		//ShapeGrid(){};
		ShapeGrid(int coordX, int coordY, int coordZ)
		:m_coordX(coordX), m_coordY(coordY), m_coordZ(coordZ){}

		inline int get_CoordX() const { return m_coordX; }

		inline int get_CoordY() const { return m_coordY; }

		inline int get_CoordZ() const { return m_coordZ; }
	};
}