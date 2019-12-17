#pragma once

#include <GL/glew.h>
#include <cmath>
#include <iostream>

#include "glm.hpp"

namespace glimac
{
	class FreeflyCamera
	{
	private:
		glm::vec3 m_Position;
		float m_fPhi;
		float m_fTheta;
		glm::vec3 m_FrontVector;
		glm::vec3 m_LeftVector;
		glm::vec3 m_UpVector;

		const double PI = 3.141592653589;
  		const double HALF_PI = PI/2;



		void computeDirectionVectors()
		{
			m_FrontVector = glm::vec3(std::cos(m_fTheta)*std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta)*std::cos(m_fPhi));
			m_LeftVector = glm::vec3(std::sin(m_fPhi+HALF_PI), 0, std::cos(m_fPhi+HALF_PI));
			m_UpVector = glm::cross(m_FrontVector, m_LeftVector); 
		}

	public:

		FreeflyCamera()
		{
			m_Position = {0.f,0.f,0.f};
			m_fPhi = PI; 
			m_fTheta = 0.f;
			computeDirectionVectors();
		}

		void moveLeft(const float &t)
		{
			m_Position += t * m_LeftVector; 
		}

		void moveFront(const float &t)
		{
			m_Position += t * m_FrontVector;
		}

		void moveUp(const float &t) {
	         m_Position += t * m_UpVector;
	    }

		void rotateLeft(const float &degrees)
		{
			m_fPhi -= glm::radians(degrees);
			computeDirectionVectors();
		}

		void rotateUp(const float &degrees)
		{
			m_fTheta -= glm::radians(degrees);
			computeDirectionVectors();
		}

		glm::mat4 getViewMatrix() const 
		{
			return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
		} 

	};
}