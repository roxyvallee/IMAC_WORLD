#pragma once

#include <vector>
#include "common.hpp"
#include "Grid.hpp"
#include "Structure.hpp"
#include "FreeflyCamera.hpp"
#include "FilePath.hpp"
#include "Program.hpp"
#include "Texture.hpp"

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
			const GLuint VERTEX_ATTRIB_POSITION = 0;
			const GLuint VERTEX_ATTRIB_NORMAL = 1;
			const GLuint VERTEX_ATTRIB_TEXCOORDS = 2;
			const int WINDOW_WIDTH = 800;
			const int WINDOW_HEIGHT = 600;

			std::vector<ShapeVertex> m_Vertices;
			GLsizei m_nVertexCount;
			GLuint m_vao;
			GLuint m_vbo;

			glm::vec4 m_lightDir;
			glm::vec4 m_lightPos;

			GLint m_uLightDir_vs;
			GLint m_uLightPos_vs;

			void add_up_face();
			void add_down_face();
			void add_front_face();
			void add_back_face();
			void add_left_face();
			void add_right_face();

		public:
		
			int m_type;
			Cube();
			/// \brief find the begin of tab vertice
			/// \return the begin of tab vertice
			inline const ShapeVertex* getDataPointer() const { return &m_Vertices[0];}

			/// \brief find the number of vertex
			/// \return the number of vertex
			inline GLsizei getVertexCount() const { return m_nVertexCount;}

			/// \brief find the VAO
			/// \return the VAO
			inline GLuint getVAO(){ return m_vao; };

			/// \brief find the VBO
			/// \return the VBO
			inline GLuint getVBO(){ return m_vbo; };

			/// \brief find the direction of directionnal light
			/// \return the direction of directionnal light
			inline glm::vec4& getLightD(){ return m_lightDir; };

			/// \brief find the direction of position light
			/// \return the direction of position light
			inline glm::vec4& getLightP(){ return m_lightPos; };

			/// \brief find the direction of directionnal light
			/// \return the direction of directionnal light
			inline GLint getULightDir(){ return m_uLightDir_vs; };

			/// \brief find the direction of position light
			/// \return the direction of position light	
			inline GLint getULightPos(){ return m_uLightPos_vs; };

			void initBufferCube();

			/// \brief draw cube with light
			/// \param : the grid, int i, the camera, the program of shaders, button day, button night and the texture
			template <typename T>
			void drawCube(Grid &maGrid, const int i, FreeflyCamera camera, const T &program, int clickDay, int clickNight, Texture &flower){
				program.m_Program.use();
		    	glUniform1i(program.uTexture, 0);

				const glm::mat4 ProjMatrix = glm::perspective( glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.f);

				const glm::mat4 ViewMatrix = camera.getViewMatrix(); // pour placer notre caméra

				glm::mat4 ModelMatrix;
		        const glm::mat4 NormalMatrix;
		        glm::mat4 MVMatrix = camera.getViewMatrix();

		        // Shininess
		        glUniform1f(program.uShininess, 100.0f);
		        glUniform3fv(program.uKd,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
		        glUniform3fv(program.uKs,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));

		    	m_lightDir =  ViewMatrix * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		    	m_uLightDir_vs = program.uLightDir_vs;
		        glUniform3f(m_uLightDir_vs, m_lightDir.x, m_lightDir.y, m_lightDir.z);
		        
		        m_lightPos =  ViewMatrix * glm::vec4(1.0f, -5.0f, 1.0f, 0.0f);
		        m_uLightPos_vs = program.uLightPos_vs;
		        glUniform3f(m_uLightPos_vs, m_lightPos.x, m_lightPos.y, m_lightPos.z);
		        
		        glUniform3fv(program.uAmbiantLightIntensity, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));	

		        if(clickDay &1){
		        	addLight(program);
		        }

		        if(clickNight &1){
		        	removeLight(program);
		        }
		       
	            MVMatrix = glm::translate(ViewMatrix, glm::vec3(2*maGrid.getX_Grid(i), 2*maGrid.getY_Grid(i), 2*maGrid.getZ_Grid(i)));
	           
	            glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
	            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
	            glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));   
	            glUniform3fv(program.uCubeColor, 1, glm::value_ptr(maGrid.getColor_Grid(i))); 

	            glActiveTexture(GL_TEXTURE0);
		        glBindTexture(GL_TEXTURE_2D, flower.getId());
		            glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		        glBindTexture(GL_TEXTURE_2D, 0);
		       	glActiveTexture(GL_TEXTURE0); 
			}

			/// \brief add the directionnal light and reset position light
			/// \param : program of shader
			template <typename T>
			void addLight(const T &program){
		        // Light variables
		        glUniform3fv(program.uLightIntensityD, 1, glm::value_ptr(glm::vec3(5.f, 5.f, 5.f)));
		        glUniform3fv(program.uLightIntensityP, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
			}
			
			/// \brief add the position light and reset directionnal light
			/// \param : program of shader
			template <typename T>
			void removeLight(const T &program){
		        // Light variables
		        glUniform3fv(program.uLightIntensityP, 1, glm::value_ptr(glm::vec3(50.f, 50.f, 50.f)));
		        glUniform3fv(program.uLightIntensityD, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
			}

			/// \brief change the position of the lights
			/// \param : positon of the directionnal light, position of the position light
			void changeDirectiveLightPosition(GLint uLightDir_vs, glm::vec4 dirLightX, glm::vec4 dirPosX){
				glUniform3f(m_uLightDir_vs, m_lightDir.x, m_lightDir.y, m_lightDir.z);
				glUniform3f(m_uLightPos_vs, m_lightPos.x, m_lightPos.y, m_lightPos.z);
			}
			
			void deleteBufferCube();
	};
}