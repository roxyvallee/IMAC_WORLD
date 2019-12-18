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



		void computeDirectionVectors();
		

	public:

		FreeflyCamera();
		

		void moveLeft(const float &t);

		void moveFront(const float &t);

		void moveUp(const float &t);

		void rotateLeft(const float &degrees);

		void rotateUp(const float &degrees);

		inline glm::mat4 getViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector); } 

	};
}