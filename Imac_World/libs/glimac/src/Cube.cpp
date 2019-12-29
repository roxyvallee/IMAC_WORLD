#include <iostream>
#include <glm/glm.hpp>
#include "glimac/Cube.hpp"

namespace glimac{

	void Cube::add_up_face()
	{
		glm::vec3 up_normal = {0.f, y_up, 0.f };

		ShapeVertex left_up_back { glm::vec3(x_left, y_up, z_back), up_normal, glm::vec2(0.f, 0.f) };
		ShapeVertex right_up_back { glm::vec3(x_right, y_up, z_back), up_normal, glm::vec2(1.f, 0.f) };
		ShapeVertex left_up_front { glm::vec3(x_left, y_up, z_front), up_normal, glm::vec2(0.f, 1.f) };
		ShapeVertex right_up_front { glm::vec3(x_right, y_up, z_front), up_normal, glm::vec2(1.f, 1.f) };

		m_Vertices.push_back(left_up_back);
		m_Vertices.push_back(left_up_front);
		m_Vertices.push_back(right_up_front);

		m_Vertices.push_back(left_up_back);
		m_Vertices.push_back(right_up_back);
		m_Vertices.push_back(right_up_front);

	}

	void Cube::add_down_face()
	{
		glm::vec3 down_normal = {0.f, y_down, 0.f };

		ShapeVertex left_down_back { glm::vec3(x_left, y_down, z_back), down_normal, glm::vec2(0.f, 0.f) };
		ShapeVertex right_down_back { glm::vec3(x_right, y_down, z_back), down_normal, glm::vec2(1.f, 0.f) };
		ShapeVertex left_down_front { glm::vec3(x_left, y_down, z_front), down_normal, glm::vec2(0.f, 1.f) };
		ShapeVertex right_down_front { glm::vec3(x_right, y_down, z_front), down_normal, glm::vec2(1.f, 1.f) };

		m_Vertices.push_back(left_down_back);
		m_Vertices.push_back(left_down_front);
		m_Vertices.push_back(right_down_front);

		m_Vertices.push_back(left_down_back);
		m_Vertices.push_back(right_down_back);
		m_Vertices.push_back(right_down_front);

	}

	void Cube::add_front_face()
	{
		glm::vec3 front_normal = {0.f, 0.f, z_front};

		ShapeVertex left_up_front { glm::vec3(x_left, y_up, z_front), front_normal, glm::vec2(0.f, 0.f) };
		ShapeVertex right_up_front{ glm::vec3(x_right, y_up, z_front), front_normal, glm::vec2(1.f, 0.f) };
		ShapeVertex left_down_front { glm::vec3(x_left, y_down, z_front), front_normal, glm::vec2(0.f, 1.f) };
		ShapeVertex right_down_front { glm::vec3(x_right, y_down, z_front), front_normal, glm::vec2(1.f, 1.f) };

		m_Vertices.push_back(left_up_front);
		m_Vertices.push_back(right_up_front);
		m_Vertices.push_back(right_down_front);

		m_Vertices.push_back(left_up_front);
		m_Vertices.push_back(left_down_front);
		m_Vertices.push_back(right_down_front);
	}

	void Cube::add_back_face()
	{
		glm::vec3 back_normal = {0.f, 0.f, z_back};

		ShapeVertex left_up_back { glm::vec3(x_left, y_up, z_back), back_normal, glm::vec2(0.f, 0.f) };
		ShapeVertex right_up_back{ glm::vec3(x_right, y_up, z_back), back_normal, glm::vec2(1.f, 0.f) };
		ShapeVertex left_down_back { glm::vec3(x_left, y_down, z_back), back_normal, glm::vec2(0.f, 1.f) };
		ShapeVertex right_down_back { glm::vec3(x_right, y_down, z_back), back_normal, glm::vec2(1.f, 1.f) };

		m_Vertices.push_back(left_up_back);
		m_Vertices.push_back(right_up_back);
		m_Vertices.push_back(right_down_back);

		m_Vertices.push_back(left_up_back);
		m_Vertices.push_back(left_down_back);
		m_Vertices.push_back(right_down_back);
	}

	void Cube::add_left_face()
	{
		glm::vec3 left_normal = {x_left, 0.f, 0.f};

		ShapeVertex left_up_front { glm::vec3(x_left, y_up, z_front), left_normal, glm::vec2(0.f, 0.f) };
		ShapeVertex left_up_back { glm::vec3(x_left, y_up, z_back), left_normal, glm::vec2(1.f, 0.f) };
		ShapeVertex left_down_front { glm::vec3(x_left, y_down, z_front), left_normal, glm::vec2(0.f, 1.f) };
		ShapeVertex left_down_back { glm::vec3(x_left, y_down, z_back), left_normal, glm::vec2(1.f, 1.f) };

		m_Vertices.push_back(left_up_front);
		m_Vertices.push_back(left_up_back);
		m_Vertices.push_back(left_down_back);

		m_Vertices.push_back(left_up_front);
		m_Vertices.push_back(left_down_front);
		m_Vertices.push_back(left_down_back);
	}

	void Cube::add_right_face()
	{
		glm::vec3 right_normal = {x_right, 0.f, 0.f};

		ShapeVertex right_up_front { glm::vec3(x_right, y_up, z_front), right_normal, glm::vec2(0.f, 0.f) };
		ShapeVertex right_up_back { glm::vec3(x_right, y_up, z_back), right_normal, glm::vec2(1.f, 0.f) };
		ShapeVertex right_down_front { glm::vec3(x_right, y_down, z_front), right_normal, glm::vec2(0.f, 1.f) };
		ShapeVertex right_down_back { glm::vec3(x_right, y_down, z_back), right_normal, glm::vec2(1.f, 1.f) };

		m_Vertices.push_back(right_up_front);
		m_Vertices.push_back(right_up_back);
		m_Vertices.push_back(right_down_back);

		m_Vertices.push_back(right_up_front);
		m_Vertices.push_back(right_down_front);
		m_Vertices.push_back(right_down_back);
	}

	Cube::Cube() : m_type(0){
		add_up_face();
		add_down_face();
		add_front_face();
		add_back_face();
		add_left_face();
		add_right_face();
			
		m_nVertexCount = m_Vertices.size();
	}

	void Cube::initBufferCube(){
	    glGenBuffers(1, &m_vbo);

	    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	        glBufferData(GL_ARRAY_BUFFER, getVertexCount()*sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    glGenVertexArrays(1, &m_vao);

	    glBindVertexArray(m_vao);     

	        glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
	        glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
	        glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS);

	        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	            glVertexAttribPointer(VERTEX_ATTRIB_POSITION,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, position)));
	            glVertexAttribPointer(VERTEX_ATTRIB_NORMAL,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, normal)));
	            glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS,2,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, texCoords)));
	        glBindBuffer(GL_ARRAY_BUFFER,0);

	    glBindVertexArray(0);
	}

	void Cube::deleteBufferCube(){
		glDeleteBuffers(1,&m_vbo);
   		glDeleteVertexArrays(1,&m_vao);
	}
}

























