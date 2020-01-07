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

		// constructor
		Cursor();

		// destructor
		~Cursor() {};

		/// \brief move the cursor to the left
		void moveLeft();

		/// \brief move the cursor to the right
		void moveRight();

		/// \brief move up the cursor 
		void moveUp();	

		/// \brief move down the cursor 
		void moveDown();

		/// \brief move front the cursor 
		void moveFront();

		/// \brief move back the cursor 
		void moveBack();

		/// \brief get the position x of the cursor
		/// \return x of the cursor
		inline int getX_Cursor() const { return m_cursorX; }

		/// \brief get the position y of the cursor
		/// \return y of the cursor
		inline int getY_Cursor() const { return m_cursorY; }

		/// \brief get the position z of the cursor
		/// \return z of the cursor
		inline int getZ_Cursor() const { return m_cursorZ; }

		/// \brief create a cube cursor thank to the positions of the cursor
		/// \param cursorX, cursorY, cursorZ, Grid, camera, program
        void drawCube(int m_cursorX, int m_cursorY, int m_cursorZ, Grid maGrid, FreeflyCamera camera, const CubeProgram &program);

	};
}
