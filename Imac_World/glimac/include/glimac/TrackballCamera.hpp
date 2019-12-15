#pragma once

#include <GL/glew.h>
#include <cmath>
#include "glm.hpp"

namespace glimac
{
	class TrackballCamera {

		private :

		float m_fDistance;
		float m_fAngleX;
		float m_fAngleY;

		public :
		TrackballCamera()
		{
			m_fDistance = 1.0;
			m_fAngleX = 0.0;
			m_fAngleY = 0.0;
		}

		void moveFront(float delta)
		{
			if(delta >= 0)
			{
				m_fDistance --;
			}
			else
			{
				m_fDistance ++;
			}
		}

		void rotateLeft(float degrees)
		{
			m_fAngleY += degrees;
		}

		void rotateUp( float degrees)
		{
			m_fAngleX += degrees;
		}

		glm::mat4 getViewMatrix() const
		{
			glm::mat4 ViewMatrix = glm::translate(glm::mat4(), glm::vec3(0,0,-m_fDistance));
			ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleX), glm::vec3(1,0,0));
			ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleY), glm::vec3(0,1,0));

			return ViewMatrix;
		}


	};
}

