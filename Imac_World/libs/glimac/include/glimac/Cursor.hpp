#pragma once

#include <vector>
#include "Grid.hpp"

namespace glimac{

	class Cursor
	{
	private:
		int m_cursorX; 
		int m_cursorY;
		int m_cursorZ;

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
	};
}
