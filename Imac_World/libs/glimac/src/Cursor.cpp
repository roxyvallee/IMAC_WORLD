#include <iostream>
#include "glimac/Cursor.hpp"

namespace glimac{

	Cursor::Cursor()
	{
		m_cursorX = 0;
		m_cursorY = 0;
		m_cursorZ = 0;
	}

	void Cursor::moveLeft()
	{
		m_cursorX += -1;
	}

	void Cursor::moveRight()
	{
		m_cursorX += 1;
	}

	void Cursor::moveUp()
	{
		m_cursorY += 1;
	}	

	void Cursor::moveDown()
	{
		m_cursorY += -1;
	}

	void Cursor::moveFront()
	{
		m_cursorZ += 1;
	}

	void Cursor::moveBack()
	{
		m_cursorZ += -1;
	}
}