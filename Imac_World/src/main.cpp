#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Grid.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Above.hpp>
#include <glimac/Structure.hpp>
#include <glimac/Texture.hpp>
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

using namespace glimac;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char** argv) {

	/*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    glEnable(GL_DEPTH_TEST);

    Cube cube;
    FreeflyCamera camera;
    Grid maGrid;
    Cursor cursor;
    Above above;
    Texture flower("../Imac_World/assets/textures/flower.jpg"); 
    Texture grass("../Imac_World/assets/textures/grass.jpg"); 

    // Initialize Imgui window
    above.initImgui(windowManager.m_window, &windowManager.m_glContext);

    FilePath applicationPath(argv[0]);
    CubeProgram cubeProgram(applicationPath);
    CubeProgramTexture cubeProgramTexture(applicationPath);

    cube.initBufferCube();
    cursor.initBufferCube();

    bool mouseDown = false;
    int mouseX = 0, mouseY = 0;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            // Send event to ImGui
            ImGui_ImplSDL2_ProcessEvent(&e);

            // Pas de SDL event quand on touche à la fenêtre ImGui
            above.getIO() = ImGui::GetIO();
            if(above.getIO().WantCaptureMouse){
                ImGui::CaptureKeyboardFromApp(true);
            }
            else{
                ImGui::CaptureKeyboardFromApp(false);
            }

            if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_ESCAPE)){
                done = true;
                break;
            }

            switch(e.type) {

                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONDOWN:
                    mouseY = e.button.y;
                    mouseX = e.button.x;
                    mouseDown = true;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    mouseDown = false;
                    break;
            
                case SDL_MOUSEMOTION:                
                    if (mouseDown) {
                        camera.rotateLeft(e.button.x - mouseX);
                        camera.rotateUp(e.button.y - mouseY);
                        mouseX = e.button.x;
                        mouseY = e.button.y;
                    }
                    break;

                case SDL_KEYDOWN:
                    if (e.key.keysym.sym=='z'){ 
                        camera.moveFront(1);
                    }
                     if (e.key.keysym.sym=='s'){ 
                        camera.moveFront(-1);
                    }
                    if (e.key.keysym.sym=='q'){ 
                        camera.moveLeft(1);
                    }
                     if (e.key.keysym.sym=='d'){ 
                        camera.moveLeft(-1);
                    }
                    if (e.key.keysym.sym=='w'){ 
                        camera.moveUp(1);
                    }
                     if (e.key.keysym.sym=='x'){ 
                        camera.moveUp(-1);
                    }
                    if (e.key.keysym.sym== SDLK_LEFT){ 
                        cursor.moveLeft();
                    }
                     if (e.key.keysym.sym==SDLK_RIGHT){ 
                        cursor.moveRight();
                    }
                    if (e.key.keysym.sym==SDLK_UP){ 
                        cursor.moveUp();
                    }
                     if (e.key.keysym.sym==SDLK_DOWN){ 
                        cursor.moveDown();
                    }
                    if (e.key.keysym.sym=='l'){ 
                        cursor.moveFront();
                    }
                     if (e.key.keysym.sym=='m'){ 
                        cursor.moveBack();
                    }
                    break;

                case SDL_KEYUP:
                    break;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClearColor(0.439216f, 0.576471f, 0.858824f, 0.0f); //background bleu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        above.beginFrame(windowManager.m_window);
        
#pragma region CUBE

        glBindVertexArray(cube.getVAO());

        for(int i=0; i < maGrid.getGridSize(); i++)
        {
            if( maGrid.getType_Grid(i) == 0)
            {
                cube.drawCube(maGrid, i, camera, cubeProgram, above.getClickDay(), above.getClickNight(), flower); 
            }
            else
            {
                switch(maGrid.getType_Grid(i)){
                    case 1:
                        cube.drawCube(maGrid, i, camera, cubeProgramTexture, above.getClickDay(), above.getClickNight(), flower); 
                    break; 
                    case 2:
                        cube.drawCube(maGrid, i, camera, cubeProgramTexture, above.getClickDay(), above.getClickNight(), grass); 
                    break; 
                default:
                    std::cerr << "no texture selected" << std::endl;
                }  
            }
        }
        
        cursor.drawCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor(), maGrid, camera, cubeProgram);

        glBindVertexArray(0);

#pragma endregion CUBE


#pragma region IMGUI

        above.drawAbove(WINDOW_WIDTH, WINDOW_HEIGHT, maGrid[maGrid.findCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor())], maGrid, cube);
        if(above.getClickCreateCube() &1) {
            //ajouter notre cube
            maGrid.createCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor());
        }
        if(above.getClickDeleteCube() &1) {
            //delete notre cube
            maGrid.deleteCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor());
        }
        if(above.getClickExtrudeCube() &1) {
            //extruder notre cube
            maGrid.extrudeCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor());
        }
        if(above.getClickDigCube() &1) {
            //delete notre cube
            maGrid.digCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor());
        }
        if(above.getClickGenerateWorld() &1) {
            //generate a world thanks to radial basis functions
            maGrid.generateWorld(10);
        }
        if(above.getClickResetAll() &1) {
            //reset all cubes
            maGrid.resetCube();
        }
        if(above.getClickTextureFlower() &1) {
            //active texture flower
            maGrid.changeType(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor(), 1);
        }
        if(above.getClickTextureGrass() &1) {
            //active texture flower
            maGrid.changeType(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor(), 2);
        }
        if(above.getClickColor() &1) {
            //active color
            maGrid.changeType(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor(), 0);
        }
        if(!above.getSaveName().empty())
        {
            //save file
            maGrid.writeFile(above.getSaveName());
            above.getSaveName().clear();
        }
        if(!above.getOpenName().empty())
        {
            //open file
            maGrid.readFile(above.getOpenName());
            above.getOpenName().clear();
        }
        above.clearString();
        above.endFrame(windowManager.m_window);

#pragma endregion IMGUI

        // Update the display
        windowManager.swapBuffers();

    }

    cube.deleteBufferCube();
 
    return EXIT_SUCCESS;
}
