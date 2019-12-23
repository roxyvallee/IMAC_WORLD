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

	void Cursor::drawCube(int m_cursorX, int m_cursorY, int m_cursorZ, Grid maGrid, FreeflyCamera camera, const std::string& filepath){
		FilePath applicationPath(filepath);
		CubeProgram cubeProgram(applicationPath);
		cubeProgram.m_Program.use();

		const glm::mat4 ProjMatrix2 = glm::perspective( glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.f);
		const glm::mat4 ViewMatrix2 = camera.getViewMatrix(); // pour placer notre caméra
		const glm::mat4 NormalMatrix2;
        glm::mat4 MVMatrix2 = camera.getViewMatrix();

        MVMatrix2 = glm::translate(ViewMatrix2, glm::vec3(2*getX_Cursor(), 2*getY_Cursor(), 2*getZ_Cursor()));
            
        glUniformMatrix4fv(cubeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix2)); // Value
        glUniformMatrix4fv(cubeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix2)))); // Value
        glUniformMatrix4fv(cubeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix2 * MVMatrix2)); // Value  
        glUniform3fv(cubeProgram.uCubeColor, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f))); // Value 

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);
			glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}