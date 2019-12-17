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
		Cursor()
		{
			m_cursorX = 0;
			m_cursorY = 0;
			m_cursorZ = 0;
		}

		void moveLeft()
		{
			m_cursorX += -1;
		}

		void moveRight()
		{
			m_cursorX += 1;
		}
		
		void moveUp()
		{
			m_cursorY += 1;
		}	

		void moveDown()
		{
			m_cursorY += -1;
		}

		void moveFront()
		{
			m_cursorZ += 1;
		}

		void moveBack()
		{
			m_cursorZ += -1;
		}

		int getX_Cursor() const
		{
			return m_cursorX;
		}
		
		int getY_Cursor() const
		{
			return m_cursorY;
		}

		int getZ_Cursor() const
		{
			return m_cursorZ;
		}
	};
}