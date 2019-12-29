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

			void add_up_face();
			void add_down_face();
			void add_front_face();
			void add_back_face();
			void add_left_face();
			void add_right_face();

		public:
		
			int m_type;
			Cube();
			inline const ShapeVertex* getDataPointer() const { return &m_Vertices[0];}
			inline GLsizei getVertexCount() const { return m_nVertexCount;}
			inline GLuint getVAO(){ return m_vao; };
			inline GLuint getVBO(){ return m_vbo; };
			void initBufferCube();

			template <typename T>
			void drawCube(Grid &maGrid, const int i, FreeflyCamera camera, const T &program, int clickDay, int clickNight, Texture &flower){
				program.m_Program.use();
				//Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 0 
		    	//pour lire dans la texture uTexture:
		    	glUniform1i(program.uTexture, 0);

				const glm::mat4 ProjMatrix = glm::perspective( glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.f);

				const glm::mat4 ViewMatrix = camera.getViewMatrix(); // pour placer notre caméra

				glm::mat4 ModelMatrix;
		        const glm::mat4 NormalMatrix;
		        glm::mat4 MVMatrix = camera.getViewMatrix();


		        // Shininess
		        glUniform1f(program.uShininess, 50.0f);
		        glUniform3fv(program.uKd,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
		        glUniform3fv(program.uKs,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));

		    	glm::vec4 lightDir =  ViewMatrix * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		        glUniform3f(program.uLightDir_vs, lightDir.x, lightDir.y, lightDir.z);
		        glm::vec4 lightPos =  ViewMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		        glUniform3f(program.uLightPos_vs, lightPos.x, lightPos.y, lightPos.z);
		        
		        glUniform3fv(program.uAmbiantLightIntensity, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));	

		        if(clickDay &1){
		        	addLight(program, ViewMatrix);
			        std::cout << "day" << std::endl;
		        }

		        if(clickNight &1){
		        	removeLight(program, ViewMatrix);
			        std::cout << "night" << std::endl;
		        }
		       
	            MVMatrix = glm::translate(ViewMatrix, glm::vec3(2*maGrid.getX_Grid(i), 2*maGrid.getY_Grid(i), 2*maGrid.getZ_Grid(i)));
	           
	            glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); // Value
	            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix)))); // Value
	            glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); // Value  
	            glUniform3fv(program.uCubeColor, 1, glm::value_ptr(maGrid.getColor_Grid(i))); // Value  

	            glActiveTexture(GL_TEXTURE0);
		        glBindTexture(GL_TEXTURE_2D, flower.getId());
		            glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		        glBindTexture(GL_TEXTURE_2D, 0);
		       	glActiveTexture(GL_TEXTURE0); 
			}

			template <typename T>
			void addLight(const T &program, const glm::mat4 ViewMatrix){
		        // Light variables
		        glUniform3fv(program.uLightIntensityD, 1, glm::value_ptr(glm::vec3(5.f, 5.f, 5.f)));
		        glUniform3fv(program.uLightIntensityP, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
		         std::cout << "add light" << std::endl;
			}
			
			template <typename T>
			void removeLight(const T &program, const glm::mat4 ViewMatrix){
		        // Light variables
		        glUniform3fv(program.uLightIntensityP, 1, glm::value_ptr(glm::vec3(5.f, 5.f, 5.f)));
		        glUniform3fv(program.uLightIntensityD, 1, glm::value_ptr(glm::vec3(0.f, 0.f, 0.f)));
		        std::cout << "remove light" << std::endl;

			}
			void deleteBufferCube();
	};
}