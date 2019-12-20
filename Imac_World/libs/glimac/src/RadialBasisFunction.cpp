#include "glimac/RadialBasisFunction.hpp"
#include <Eigen/Dense>

namespace glimac{


    double RadialBasisFunction::distance(glm::vec3 A, glm::vec3 B)
    {
        return sqrt( std::pow(A[0]-B[0], 2) + std::pow(A[1]-B[1], 2) + std::pow(A[2]-B[2], 2));
    }

    double RadialBasisFunction::radialFunctionGauss( glm::vec3 A, glm::vec3 B)
    {
        return glm::exp(- std::pow(distance(A,B), 2));
        //return glm::exp(-std::pow(glm::distance(A,B),2));
    }

    //double RadialBasisFunction::radialFunction


    Eigen::VectorXd RadialBasisFunction::findOmega()
    {
        Eigen::MatrixXd M = Eigen::MatrixXd::Zero(m_ValuePoint.size(),m_ValuePoint.size()); 
        for(int i=0; i<m_ValuePoint.size(); i++)
        {
            for(int j =0; j<m_ValuePoint.size(); j++)
            {
                M(i,j) = radialFunctionGauss(m_Points[i], m_Points[j]);
            }    
        }
        return M.inverse()*m_ValuePoint;
        //return M.colPivHouseholderQr().solve(m_ValuePoint);
    } 

    RadialBasisFunction::RadialBasisFunction()
        : m_ValuePoint(3), m_Omega(3)
    {
        m_Points.push_back(glm::vec3(0.f, 0.f, 0.f));
        m_Points.push_back(glm::vec3(10.f, 0.f, 0.f));
        m_Points.push_back(glm::vec3(0.f,5.f, 5.f));
        //std::cout<< "3/ ça marche jusque ici" << std::endl;
        
        //m_ValuePoint << 30.0, 8.0, 4.0;
        m_ValuePoint[0] = 30.0;
        m_ValuePoint[1] = -8.0;
        //std::cout<< "4/ ça marche jusque ici" << std::endl;
        m_ValuePoint[2] = -4.0;

        //std::cout<< "5/ ça marche jusque ici" << std::endl;
        m_Omega = findOmega();
    }

    
    double RadialBasisFunction::calculBasisFunction(glm::vec3 V)
    {
        double sum = 0.0;
        //std::cout<< "6/ ça marche jusque ici" << std::endl;
        for(int i = 0; i < m_Omega.size(); i++)
        {
            sum += m_Omega[i] * radialFunctionGauss(m_Points[i], V);
        }
        //std::cout<< "7/ ça marche jusque ici" << std::endl;
        return sum;
    }

}






