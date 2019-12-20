#include <iostream>
#include "glimac/Grid.hpp"
#include "glimac/RadialBasisFunction.hpp"

namespace glimac{
	
	Grid::Grid()
	{
		// cube 1 en [0,0,0]
			m_Grid.push_back(ShapeGrid(0,0,0, glm::vec3(1.f, 0.f, 0.f)));
			// cube 2 en [1,0,0]
			m_Grid.push_back(ShapeGrid(1,0,0, glm::vec3(0.f, 1.f, 0.f)));
			// cube 3 en [-1,0,0]
			m_Grid.push_back(ShapeGrid(-1,0,0, glm::vec3(0.f, 0.f, 1.f)));

			m_sizeGrid = m_Grid.size();
	}
	

	Grid::Grid(int iterator)
	{
		//std::cout<< "2/ ça marche jusque ici" << std::endl;
		RadialBasisFunction test;
		for(int i=0; i<iterator; i++)
		{
			for(int j=0; j<iterator; j++)
			{
				for(int k=0; k<iterator;k++)
				{
					glm::vec3 v = {i,j,k};
					if(test.calculBasisFunction(v) >= 0.0)
					{
						//std::cout<< "8/ ça marche jusque ici : " << test.calculBasicFunction(v) << std::endl;
						//createCube(i,j,k);
						m_Grid.push_back(ShapeGrid(i,j,k, glm::vec3(0.f, 0.f, 1.f)));
						m_sizeGrid = m_Grid.size();
						//std::cout<< "9/ ça marche jusque ici" << std::endl;
					}
				}
			}
		}
	}

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
			m_Grid.push_back(ShapeGrid(x,y,z, glm::vec3(0.f, 0.f, 1.f)));
			m_sizeGrid = m_Grid.size();
		}
		else 
			std::cerr << "cube already exist" << std::endl;
	}

	void Grid::changeColor(const int x, const int y, const int z, const glm::vec3 color)
	{
		if(findCube(x,y,z) != -1)
		{
			m_Grid[findCube(x,y,z)].set_Color(color);
		}
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

	void Grid::resetCube()
	{
		m_Grid.clear();
	}

}