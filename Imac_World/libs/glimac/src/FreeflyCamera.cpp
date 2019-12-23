#include <iostream>
#include "glimac/FreeflyCamera.hpp"

namespace glimac
{
	void FreeflyCamera::computeDirectionVectors()
	{
			m_FrontVector = glm::vec3(std::cos(m_fTheta)*std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta)*std::cos(m_fPhi));
			m_LeftVector = glm::vec3(std::sin(m_fPhi+HALF_PI), 0, std::cos(m_fPhi+HALF_PI));
			m_UpVector = glm::cross(m_FrontVector, m_LeftVector); 
	}

	FreeflyCamera::FreeflyCamera()
	{
		m_Position = {0.f,0.f,25.f};
		m_fPhi = PI; 
		m_fTheta = 0.f;
		computeDirectionVectors();
	}

	void FreeflyCamera::moveLeft(const float &t)
	{
		m_Position += t * m_LeftVector; 
	}


	void FreeflyCamera::moveFront(const float &t)
	{
		m_Position += t * m_FrontVector;
	}

	void FreeflyCamera::moveUp(const float &t) 
	{
    	m_Position += t * m_UpVector;
	}

	void FreeflyCamera::rotateLeft(const float &degrees)
	{
		m_fPhi -= glm::radians(degrees);
		computeDirectionVectors();
	}

	void FreeflyCamera::rotateUp(const float &degrees)
	{
		m_fTheta -= glm::radians(degrees);
		computeDirectionVectors();
	}




}