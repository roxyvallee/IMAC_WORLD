#ifndef _ABOVE_HPP 
#define _ABOVE_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <glimac/glm.hpp>
#include "glimac/ShapeGrid.hpp"

namespace glimac
{
	class Above
	{
		public:
			// Constructor
			Above(){};
			//Destructor
			~Above();
			void initImgui(SDL_Window* window,SDL_GLContext* glContext) const;
			void beginFrame(SDL_Window* window) const;
			void drawAbove(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, ShapeGrid &cubeSelect);
    		void endFrame(SDL_Window* window) const;
    		inline int getClickCreateCube(){return clickCreateCube;};
			inline int getClickDeleteCube(){return clickDeleteCube;};
			inline int getClickExtrudeCube(){return clickExtrudeCube;};
			inline int getClickDigCube(){return clickDigCube;};
			inline glm::vec3 getClickCubeColor(){return colorCube;};

    	private:
    		int clickCreateCube;
			int clickDeleteCube;
			int clickExtrudeCube;
        	int clickDigCube;
        	float r;
        	float g;
        	float b;
        	glm::vec3 colorCube;
	};
}

#endif 



