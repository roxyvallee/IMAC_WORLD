#pragma once

#include <vector>
#include "common.hpp"
#include "Grid.hpp"
#include "Structure.hpp"
#include "FreeflyCamera.hpp"
#include "FilePath.hpp"
#include "Program.hpp"

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
		
			Cube();
			inline const ShapeVertex* getDataPointer() const { return &m_Vertices[0];}
			inline GLsizei getVertexCount() const { return m_nVertexCount;}
			inline GLuint getVAO(){ return m_vao; };
			inline GLuint getVBO(){ return m_vbo; };
			void initBufferCube();
			void drawCube(Grid maGrid, FreeflyCamera camera, const CubeProgram &program, int clickDay, int clickNight);
			void deleteBufferCube();
			void addLight(const CubeProgram &program, const glm::mat4 ViewMatrix);
			void removeLight(const CubeProgram &program, const glm::mat4 ViewMatrix);

	};


}