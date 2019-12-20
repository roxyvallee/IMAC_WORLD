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

		double distance(glm::vec3 A, glm::vec3 B);
		double radialFunctionGauss( glm::vec3 A, glm::vec3 B);
		Eigen::VectorXd findOmega();

	public:

		RadialBasisFunction();
		double calculBasisFunction(glm::vec3 V);
	

	};
}
