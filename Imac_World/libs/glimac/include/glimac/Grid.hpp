#pragma once

#include <vector>
#include "ShapeGrid.hpp"

namespace glimac{

	class Grid
	{
	private:
		std::vector<ShapeGrid> m_Grid;
		int m_sizeGrid;

	public:
		//Grid(){};
		Grid(); // initialisation de notre univers avec 3 cubes sur la même couche
		
		inline int getGridSize() const { return m_sizeGrid; }

		inline int getX_Grid(const int &i) const { return m_Grid[i].get_CoordX();}

		inline int getY_Grid(const int &i) const { return m_Grid[i].get_CoordY();}

		inline int getZ_Grid(const int &i) const { return m_Grid[i].get_CoordZ();}

		//bool isCube(const int x, const int y, const int z);
		int findCube(const int x, const int y, const int z);
		void createCube(const int x, const int y, const int z);
		void deleteCube(const int x, const int y, const int z);

	};

}
