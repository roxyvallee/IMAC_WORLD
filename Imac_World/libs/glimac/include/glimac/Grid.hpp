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
		Grid() // initialisation de notre univers avec 3 cubes sur la même couche
		{
			// cube 1 en [0,0,0]
			m_Grid.push_back(ShapeGrid(0,0,0));
			// cube 2 en [1,0,0]
			m_Grid.push_back(ShapeGrid(1,0,0));
			// cube 3 en [-1,0,0]
			m_Grid.push_back(ShapeGrid(-1,0,0));

			m_sizeGrid = m_Grid.size();
		}

		int getGridSize() const
		{
			return m_sizeGrid;
		}

		int getX_Grid(const int &i) const
		{
			return m_Grid[i].get_CoordX();
		}

		int getY_Grid(const int &i) const
		{
			return m_Grid[i].get_CoordY();
		}

		int getZ_Grid(const int &i) const
		{
			return m_Grid[i].get_CoordZ();
		}

		bool isCube(const int x, const int y, const int z)
		{
			for(uint i=0; i< m_sizeGrid; i++)
			{
				if( x ==  m_Grid[i].get_CoordX())
				{
					if(y == m_Grid[i].get_CoordY())
					{
						if(z == m_Grid[i].get_CoordZ())
						{
							return true;
						}
						else
							return false;
					}
					else
						return false;
				}else
					return false;
			}
			return false;
		}

	};

}
