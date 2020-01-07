#pragma once

#include <vector>
#include <math.h> 
#include <iostream>
#include <Eigen/Dense>
#include <glm/glm.hpp>

namespace glimac{

	class RadialBasisFunction
	{
	private:
		std::vector<glm::vec3> m_Points;
		Eigen::VectorXd m_ValuePoint;
		Eigen::VectorXd m_Omega;


		/// \brief calculate the distance between two vectors
		/// \param A and B : the two vectors we want to calculate
		/// \return the value of the distance between two vectors
		double distance(glm::vec3 A, glm::vec3 B);

		/// \brief use the function Gauss to generate the world
		/// \param A and B : the two vectors we want to calculate
		/// \return the value of the function
		double radialFunctionGauss( glm::vec3 A, glm::vec3 B);

		/// \brief use the function Inverse Quadratic to generate the world
		/// \param A and B : the two vectors we want to calculate
		/// \return the value of the function
		double radialFunctionInverseQuadra( glm::vec3 A, glm::vec3 B);

		/// \brief use the function Multiquadratic to generate the world
		/// \param A and B : the two vectors we want to calculate
		/// \return the value of the function
		double radialFunctionMultiQuadra( glm::vec3 A, glm::vec3 B);

		/// \brief use the function Inverse Multiquadratic to generate the world
		/// \param A and B : the two vectors we want to calculate
		/// \return the value of the function
		double radialFunctionInverseMultiQuadra( glm::vec3 A, glm::vec3 B);

		/// \brief the function find the omega thank to the radial Function
		/// \return the vector of the value of Omega
		Eigen::VectorXd findOmega();

	public:

		/// \brief the constructor, create the vector m_Points and m_ValuePoint, find Omega
		RadialBasisFunction();

		/// \brief the destructor
		~RadialBasisFunction() {};

		/// \brief  calculate the value of each position in our Grid thank to Radial Basis Function
		/// \param V a vector position x,y,z 
		/// \return the value of the position
		double calculBasisFunction(glm::vec3 V);
	

	};
}
