#include <iostream>
#include "glimac/Cursor.hpp"
#include "glimac/Cube.hpp"

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

	void Cursor::drawCube(int m_cursorX, int m_cursorY, int m_cursorZ){
		/*glm::mat4 ModelMatrix;
        const glm::mat4 NormalMatrix;
        glm::mat4 MVMatrix;

        glUniformMatrix4fv(CursorCubeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); // Value
        glUniformMatrix4fv(CursorCubeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix)))); // Value
        glUniformMatrix4fv(CursorCubeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); // Value  */

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);
			glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}