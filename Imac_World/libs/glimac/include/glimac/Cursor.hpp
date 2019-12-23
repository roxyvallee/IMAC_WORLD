#pragma once

#include <vector>
#include "Grid.hpp"
#include "Program.hpp"
#include "Cube.hpp"

namespace glimac{

	class Cursor : public Cube
	{
	private:
		int m_cursorX; 
		int m_cursorY;
		int m_cursorZ;
		const int WINDOW_WIDTH = 800;
		const int WINDOW_HEIGHT = 600;

	public:

		Cursor();

		void moveLeft();
	
		void moveRight();
		
		void moveUp();	

		void moveDown();

		void moveFront();

		void moveBack();

		inline int getX_Cursor() const { return m_cursorX; }
		
		inline int getY_Cursor() const { return m_cursorY; }

		inline int getZ_Cursor() const { return m_cursorZ; }

		//Une surdéfinition ou surcharge (overloading) permet d’utiliser plusieurs méthodes qui portent le même nom au sein d’une même classe avec une signature différente.
        void drawCube(int m_cursorX, int m_cursorY, int m_cursorZ, Grid maGrid, FreeflyCamera camera, const std::string& filepath);

	};
}
