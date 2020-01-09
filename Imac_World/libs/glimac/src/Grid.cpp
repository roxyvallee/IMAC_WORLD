#include <iostream>
#include <fstream>
#include <string>
#include "glimac/Grid.hpp"
#include "glimac/RadialBasisFunction.hpp"

namespace glimac{
	
	Grid::Grid()
	{
			for(int i=0; i < 10; i++)
			{
				for(int j=0; j<10; j++)
				{
					for(int k=0; k<3; k++)
					{
						m_Grid.push_back(ShapeGrid(i,-k,j, glm::vec3(0.16f, 0.46f, 0.74f)));
					}
				}
			}
			m_sizeGrid = m_Grid.size();
	}
	

	void Grid::generateWorld(int iterator)
	{
		resetCube();
		RadialBasisFunction test;
		for(int i=0; i<iterator; i++)
		{
			for(int j=0; j<iterator; j++)
			{
				for(int k=0; k<iterator;k++)
				{
					glm::vec3 v = {i,j,k};
					// if the result is under 0, we don't create the cube
					if(test.calculBasisFunction(v) >= 0.0)
					{
						m_Grid.push_back(ShapeGrid(i,j,k, glm::vec3(i, j, k)));
						m_sizeGrid = m_Grid.size();
					}
				}
			}
		}
	}


	int Grid::findCube(const int &x, const int &y, const int &z) // return index of the cube
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

	void Grid::createCube(const int &x, const int &y, const int &z)
	{
		if(findCube(x,y,z) == -1 )
		{
			m_Grid.push_back(ShapeGrid(x,y,z, glm::vec3(x, y, z)));
			m_sizeGrid = m_Grid.size();
		}
		else 
			std::cerr << "cube already exist" << std::endl;
	}


	void Grid::createCubeColor(const int &x, const int &y, const int &z, const int type, const int &r, const int &g, const int &b)
	{
		if(findCube(x,y,z) == -1 )
		{
			m_Grid.push_back(ShapeGrid(x,y,z, glm::vec3(r, g, b)));
			m_sizeGrid = m_Grid.size();

			if(type != 0 )
			{
				changeType(x,y,z,type);
			}
			
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

	void Grid::changeType(const int x, const int y, const int z, const int type)
	{
		if(findCube(x,y,z) != -1)
		{
			m_Grid[findCube(x,y,z)].set_Type(type);
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

	void Grid::writeFile(std::string name)
	{
		std::string const nomFichier("../Imac_World/save/" + name);
		std::ofstream monFlux(nomFichier.c_str());

		if(monFlux)
		{
		
			for(int i=0; i< getGridSize(); i++)
			{
				glm::vec3 color = getColor_Grid(i); 
				monFlux << getX_Grid(i)<<" " << getY_Grid(i) <<" " <<getZ_Grid(i) << " " << getType_Grid(i) << " " << color[0] << " " << color[1] << " " << color[2] << std::endl; 
			}
		}
		else
		{
			std::cerr << "ERREUR : Impossible d'ouvrir le fichier" << std::endl;
		}
	}
	
	void Grid::readFile(std::string name)
	{
		std::ifstream myFile("../Imac_World/save/" + name);

		if(myFile)
		{
			std::string ligne;
			int ValueX;
			int ValueY;
			int ValueZ;
			int ValueType;
			int ValueR, ValueG, ValueB; 
			resetCube();
			
			while(getline(myFile, ligne) )
			{
				myFile >> ValueX;
				myFile >> ValueY;
				myFile >> ValueZ;
				myFile >> ValueType;
				myFile >> ValueR;
				myFile >> ValueG;
				myFile >> ValueB;
				
				createCubeColor(ValueX,ValueY,ValueZ,ValueType,ValueR,ValueG,ValueB);
			
			}
			myFile.close();
			
		}
		else
		{
			std::cerr << "ERREUR : Impossible d'ouvrir le fichier" << std::endl;
		}
	}
}