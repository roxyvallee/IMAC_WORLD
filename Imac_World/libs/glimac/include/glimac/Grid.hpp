#pragma once

#include <vector>
#include "ShapeGrid.hpp"
#include "RadialBasisFunction.hpp"

namespace glimac{

	class Grid
	{
	private:
		std::vector<ShapeGrid> m_Grid;
		int m_sizeGrid;

		int UpColumn(const int x, const int y, const int z);

	public:
		//Grid(){};
		Grid(); // initialisation de notre univers avec 3 cubes sur la même couche

		Grid(int iterator);

		inline ShapeGrid& operator[](int index) {return m_Grid[index];}
		
		inline int getGridSize() const { return m_sizeGrid; }

		inline int getX_Grid(const int &i) const { return m_Grid[i].get_CoordX();}

		inline int getY_Grid(const int &i) const { return m_Grid[i].get_CoordY();}

		inline int getZ_Grid(const int &i) const { return m_Grid[i].get_CoordZ();}

		inline glm::vec3 getColor_Grid(const int &i) {return m_Grid[i].get_Color();}

		//bool isCube(const int x, const int y, const int z);
		int findCube(const int &x, const int &y, const int &z);
		void createCube(const int &x, const int &y, const int &z);
		void deleteCube(const int x, const int y, const int z);
		void extrudeCube(const int x, const int y, const int z);
		void digCube(const int x, const int y, const int z);
		void changeColor(const int x, const int y, const int z, const glm::vec3 color);
		void resetCube();
	};

}
