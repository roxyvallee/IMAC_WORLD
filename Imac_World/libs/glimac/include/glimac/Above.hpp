#ifndef _ABOVE_HPP 
#define _ABOVE_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <imgui/imgui_stdlib.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <glimac/glm.hpp>
#include "glimac/ShapeGrid.hpp"
#include "glimac/Grid.hpp"

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
			ImGuiIO getIO();
			void beginFrame(SDL_Window* window) const;
			void drawAbove(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, ShapeGrid &cubeSelect, Grid &maGrid);
    		void endFrame(SDL_Window* window) const;
    		void clearString();
    		inline int getClickCreateCube(){return clickCreateCube;};
			inline int getClickDeleteCube(){return clickDeleteCube;};
			inline int getClickExtrudeCube(){return clickExtrudeCube;};
			inline int getClickDigCube(){return clickDigCube;};
			inline int getClickGenerateWorld(){return clickGenerateWorld;};
			inline int getClickResetAll(){return clickResetAll;};
			inline int getClickDay(){return clickDay;};
			inline int getClickNight(){return clickNight;};
			inline int getClickTextureFlower(){return clickTextureFlower;};
			inline int getClickColor(){return clickColor;};
			inline std::string getSaveName(){return saveName;};
			inline std::string getOpenName(){return openName;};

    	private:
    		bool p_open;
    		int clickCreateCube;
			int clickDeleteCube;
			int clickExtrudeCube;
        	int clickDigCube;
        	int clickGenerateWorld;
        	int clickResetAll;
        	int clickDay;
        	int clickNight;
        	int clickTextureFlower;
        	int clickColor;
        	std::string saveName;
        	std::string openName;

	};
}

#endif 



