#include <iostream>
#include "glimac/Grid.hpp"

namespace glimac{

	Grid::Grid()
	{
		// cube 1 en [0,0,0]
			m_Grid.push_back(ShapeGrid(0,0,0));
			// cube 2 en [1,0,0]
			m_Grid.push_back(ShapeGrid(1,0,0));
			// cube 3 en [-1,0,0]
			m_Grid.push_back(ShapeGrid(-1,0,0));

			m_sizeGrid = m_Grid.size();
	}

	/*
	bool Grid::isCube(const int x, const int y, const int z)
	{
		for(int i=0; i< m_sizeGrid; i++)
			{
				if( x ==  m_Grid[i].get_CoordX())
				{
					if(y == m_Grid[i].get_CoordY())
					{
						if(z == m_Grid[i].get_CoordZ())
						{
							return true;
						}
						
					}
					
				}


			}

			return false;	
	}
	*/



	int Grid::findCube(const int x, const int y, const int z) // return index of the cube
	{
		for(int i=0; i< m_sizeGrid; i++)
		{
			if(x ==  m_Grid[i].get_CoordX())
			{
				if(y == m_Grid[i].get_CoordY())
				{
					if(z == m_Grid[i].get_CoordZ())
					{
						return i;
					}	
				}	
			}
		}
		return -1;	
	}

	void Grid::createCube(const int x, const int y, const int z)
	{
		if(findCube(x,y,z) == -1 )
		{
			m_Grid.push_back(ShapeGrid(x,y,z));
			m_sizeGrid = m_Grid.size();
		}
		else 
			std::cerr << "cube already exist" << std::endl;
	}


	void Grid::deleteCube(const int x, const int y, const int z)
	{
		int index = findCube(x,y,z);
		if(index != -1)
		{
			m_Grid.erase(m_Grid.begin() + index);
			m_sizeGrid = m_Grid.size();
		}
		else
			std::cerr << "cube doesn't exist" << std::endl;

	} 
	
	int Grid::UpColumn(const int x, const int y, const int z)
	{
		int indexCol = y;
		while(findCube(x,indexCol,z) != -1)
		{
			indexCol++;
		}
		return indexCol;
	}
	
	void Grid::extrudeCube(const int x, const int y, const int z)
	{
		
		int positionCursor = findCube(x,y,z);
		
		if(positionCursor != -1)
		{
			
			createCube(x,UpColumn(x,y,z),z);
		}
		else
		{
			std::cerr << "can't extrud " << std::endl;
		}
	}

	void Grid::digCube(const int x, const int y, const int z)
	{
		int indexCol = UpColumn(x,y,z) - 1;

		int positionCursor = findCube(x,y,z);
		
		if(positionCursor != -1)
		{
			deleteCube(x,indexCol,z);
		}
		else
		{
			std::cerr << "can't dig " << std::endl;
		}

	}

}