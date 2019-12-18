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


	bool Grid::isCube(const int x, const int y, const int z)
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
						
					}
					
				}


			}

			return false;	
	}




	int Grid::findCube(const int x, const int y, const int z) // return index of the cube
	{
		for(uint i=0; i< m_Grid.size(); i++)
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
	}

	void Grid::createCube(const int x, const int y, const int z)
	{
		if(isCube(x,y,z) == false)
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
		if(isCube(x,y,z) == true)
		{
			m_Grid.erase(m_Grid.begin() + index);
			m_sizeGrid = m_Grid.size();
		}
		else
			std::cerr << "cube doesn't exist" << std::endl;
		
		/*int index = findCube(x,y,z);
		if(index != -1)
		{
			int lastIndex = m_Grid.size()-1;
			std::swap(m_Grid[index], m_Grid[lastIndex]);
			m_Grid.pop_back();
		}*/


	} 


}