#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "ShapeGrid.hpp"
#include "RadialBasisFunction.hpp"

namespace glimac{

	class Grid
	{
	private:
		std::vector<ShapeGrid> m_Grid;
		int m_sizeGrid;

		/// \brief find the position on the top of the colummn
		/// \param x,y,z : the position of the cursor
		/// \return the value y on the top of the column
		int UpColumn(const int x, const int y, const int z);

	public:
		
		/// \brief constructor : initilisation of the world
		Grid(); 

		/// \brief destructor
		~Grid() {};

		/// \brief find the value of Grid thank to the index by using the operator []
		/// \param index : index in Grid
		/// \return the value of the index in Grid
		inline ShapeGrid& operator[](int index) {return m_Grid[index];}
		
		/// \brief find the size of the Grid
		/// \return the value of m_sizeGrid
		inline int getGridSize() const { return m_sizeGrid; }

		/// \brief find the value of x in m_Grid 
		/// \param i : index in Grid
		/// \return the coord x in i position in m_Grid
		inline int getX_Grid(const int &i) const { return m_Grid[i].get_CoordX();}

		/// \brief find the value of y in m_Grid 
		/// \param i : index in Grid
		/// \return the coord y in i position in m_Grid
		inline int getY_Grid(const int &i) const { return m_Grid[i].get_CoordY();}

		/// \brief find the value of z in m_Grid 
		/// \param i : index in Grid
		/// \return the coord z in i position in m_Grid
		inline int getZ_Grid(const int &i) const { return m_Grid[i].get_CoordZ();}

		/// \brief find the type in m_Grid 
		/// \param i : index in Grid
		/// \return the type in i position in m_Grid
		inline int getType_Grid(const int &i) const {return m_Grid[i].get_Type();}

		/// \brief find the color in m_Grid 
		/// \param i : index in Grid
		/// \return the color in i position in m_Grid
		inline glm::vec3 getColor_Grid(const int &i) {return m_Grid[i].get_Color();}

		/// \brief generate a world thank to Radial Basis Function
		/// \param iterator : the size of the world we want to generate
		void generateWorld(int iterator);

		/// \brief find the cube in m_Grid
		/// \param x,y,z : position of the cube
		/// \return the index of the cube if exist else -1
		int findCube(const int &x, const int &y, const int &z);

		/// \brief create a cube 
		/// \param x,y,z : position of the cursor
		void createCube(const int &x, const int &y, const int &z);

		/// \brief create a cube with chosen color or texture
		/// \param x,y,z : position of the cursor
		/// \param type : if it is a color or a texture
		/// \param r,g,b : value of the color		
		void createCubeColor(const int &x, const int &y, const int &z, const int type,const int &r, const int &g, const int &b);
		
		/// \brief delete a cube 
		/// \param x,y,z : position of the cursor
		void deleteCube(const int x, const int y, const int z);

		/// \brief create a cube on the top of the column
		/// \param x,y,z : position of the cursor
		void extrudeCube(const int x, const int y, const int z);

		/// \brief delete a cube on the top of the column
		/// \param x,y,z : position of the cursor
		void digCube(const int x, const int y, const int z);

		/// \brief change color of the cube
		/// \param x,y,z : position of the cursor
		/// \param color : vector of the color 
		void changeColor(const int x, const int y, const int z, const glm::vec3 color);

		/// \brief change type of the cube
		/// \param x,y,z : position of the cursor
		/// \param type : type of the cube
		void changeType(const int x, const int y, const int z, const int type);

		/// \brief delete m_Grid, all cubes in our grid
		void resetCube();

		/// \brief save the world we create in a file
		/// \param name : the name of the file we create
		void writeFile(std::string name);

		/// \brief open the world we create in a file
		/// \param name : the name of the file we open
		void readFile(std::string name);
	};

}
