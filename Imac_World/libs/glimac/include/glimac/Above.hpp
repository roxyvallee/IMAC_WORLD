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
#include "glm.hpp"
#include "ShapeGrid.hpp"
#include "Grid.hpp"
#include "Cube.hpp"

namespace glimac
{
	class Above
	{
		public:
			/// \brief constructor
			Above(){};

			/// \brief destructor
			~Above();

			/// \brief initialize imgui
			/// \param index : window SDL, context SDL
			void initImgui(SDL_Window* window,SDL_GLContext* glContext) const;

			/// \brief find get IO for imgui
			ImGuiIO getIO();

			/// \brief initialize Imgui window
			/// \param index : window SDL
			void beginFrame(SDL_Window* window) const;

			/// \brief draw Imgui window
			/// \param index : width of the SDL window, height of the SDL window, cube selected in our shapegrid, the grid and the cube
			void drawAbove(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, ShapeGrid &cubeSelect, Grid &maGrid, Cube &cube);
    		
			/// \brief ending Imgui window
			/// \param index : window SDL
    		void endFrame(SDL_Window* window) const;

    		/// \brief clear the string
    		void clearString();

    		/// \brief find the button create cube
			/// \return the value of clickCreateCube
    		inline int getClickCreateCube(){return clickCreateCube;};

    		/// \brief find the button delete cube
			/// \return the value of clickDeleteCube
			inline int getClickDeleteCube(){return clickDeleteCube;};

			/// \brief find the button extrude cube
			/// \return the value of clickExtrudeCube
			inline int getClickExtrudeCube(){return clickExtrudeCube;};

			/// \brief find the button dig cube
			/// \return the value of clickDigCube
			inline int getClickDigCube(){return clickDigCube;};

			/// \brief find the button generate world
			/// \return the value of clickGenerateWorld
			inline int getClickGenerateWorld(){return clickGenerateWorld;};

			/// \brief find the button reset all
			/// \return the value of clickResetAll
			inline int getClickResetAll(){return clickResetAll;};

			/// \brief find the button click day
			/// \return the value of clickDay
			inline int getClickDay(){return clickDay;};

			/// \brief find the button click night
			/// \return the value of clickNight
			inline int getClickNight(){return clickNight;};

			/// \brief find the button click texture rock
			/// \return the value of clickTextureRock
			inline int getClickTextureRock(){return clickTextureRock;};

			/// \brief find the button click texture grass
			/// \return the value of clickTextureGrass
			inline int getClickTextureGrass(){return clickTextureGrass;};

			/// \brief find the button click texture sand
			/// \return the value of clickTextureSand
			inline int getClickTextureSand(){return clickTextureSand;};

			/// \brief find the button click texture water
			/// \return the value of clickTextureWater
			inline int getClickTextureWater(){return clickTextureWater;};

			/// \brief find the button click color
			/// \return the value of clickColor
			inline int getClickColor(){return clickColor;};

			/// \brief find the button save name
			/// \return the value of saveName
			inline std::string getSaveName(){return saveName;};

			/// \brief find the button open name
			/// \return the value of openName
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
        	int clickTextureRock;
        	int clickTextureGrass;
        	int clickTextureSand;
        	int clickTextureWater;
        	int clickColor;
        	std::string saveName;
        	std::string openName;

	};
}

#endif 



