#pragma once

#include <vector>
#include "common.hpp"

namespace glimac{

	class Cube
	{
		private:
			const float x_left  = -1.f;
			const float x_right = +1.f;
			const float z_back  = -1.f;
			const float z_front = +1.f;
			const float y_up    = +1.f;
			const float y_down  = -1.f;


			std::vector<ShapeVertex> m_Vertices;
			GLsizei m_nVertexCount;

			void add_up_face()
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


			void add_down_face()
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


			void add_front_face()
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

			void add_back_face()
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

			void add_left_face()
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

			void add_right_face()
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





		public:
		
		Cube()
		{

			add_up_face();
			add_down_face();
			add_front_face();
			add_back_face();
			add_left_face();
			add_right_face();
			

			/*
			m_Vertices = {
				ShapeVertex(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),// triangle 1 : begin
				ShapeVertex(glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),
				ShapeVertex(glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0,0.0,0.0), glm::vec2(0.0,0.0)),                        
                           
						};
			*/
			m_nVertexCount = m_Vertices.size();
		}

		const ShapeVertex* getDataPointer() const
		{
			return &m_Vertices[0];
		}

		GLsizei getVertexCount() const
		{
			return m_nVertexCount;
		}

	};


}