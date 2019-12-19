#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Grid.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Above.hpp>
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

using namespace glimac;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const GLuint VERTEX_ATTRIB_POSITION = 0;
const GLuint VERTEX_ATTRIB_NORMAL = 1;
const GLuint VERTEX_ATTRIB_TEXCOORDS = 2;

struct CubeProgram{
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;
    GLint uCubeColor;

    CubeProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl", applicationPath.dirPath() + "shaders/normals.fs.glsl")){
        //texture
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uCubeColor = glGetUniformLocation(m_Program.getGLId(), "uCubeColor");
        //lumière 
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};

struct Light {
    glm::vec3 intensity;
    glm::vec3 direction;

    Light(glm::vec3 inIntensity, glm::vec3 inDirection) {
        intensity = inIntensity;
        direction = inDirection;
    }
};

struct Material {
    glm::vec3 diffuse;
    glm::vec3 glossy;
    float shininess;

    Material (glm::vec3 inDiffuse, glm::vec3 inGlossy, float inShininess) {
        diffuse = inDiffuse;
        glossy = inGlossy;
        shininess = inShininess;
    }
};

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
    Light sunLight(glm::vec3(1.777,1.777,1.777), glm::vec3(1,1,1));           //création de la lumière
    Material cubeMat(glm::vec3(0.7,0.7,0.7), glm::vec3 (0.3,0.3,0.3), 10);    //création des matériaux

    // Initialize Imgui window
    above.initImgui(windowManager.m_window, &windowManager.m_glContext);

    FilePath applicationPath(argv[0]);
    CubeProgram cubeProgram(applicationPath);
    cubeProgram.m_Program.use();

    //création de la texture du cube
    /*std::unique_ptr<Image> flowerTexture = loadImage("../Imac_World/assets/textures/flower.jpg");
    if(flowerTexture == nullptr){
        std::cerr << "Erreur load image " << std::endl;
    }*/

    //Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 0 
    //pour lire dans la texture uTexture:
    //glUniform1i(cubeProgram.uTexture, 0);


    //application de la texture de la fleur
    /* GLuint texture_flower;
    glGenTextures(1, &texture_flower);
    glBindTexture(GL_TEXTURE_2D, texture_flower);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, flowerTexture->getWidth(), flowerTexture->getHeight(), 0, GL_RGBA, GL_FLOAT, flowerTexture->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
	*/

    const glm::mat4 ProjMatrix = glm::perspective( glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.f);

    cube.initBufferCube();

    bool mouseDown = false;
    int mouseX = 0, mouseY = 0;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
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
                break;

            case SDL_KEYUP:
                std::cout << "la position est : " << cursor.getX_Cursor() << "," << cursor.getY_Cursor() << ";" << cursor.getZ_Cursor() << std::endl;
                break;
            }
        }

        const glm::mat4 ViewMatrix = camera.getViewMatrix(); // pour placer notre caméra

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClearColor(0.439216f, 0.576471f, 0.858824f, 0.0f); //background bleu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        above.beginFrame(windowManager.m_window);
         
#pragma region CUBE

        cubeProgram.m_Program.use();

        glm::mat4 ModelMatrix;
        const glm::mat4 NormalMatrix;
        glm::mat4 MVMatrix = camera.getViewMatrix();
        //glm::mat4 MVMatrix = ViewMatrix * ModelMatrix;
        //ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -5.f) ); // on recule notre caméra

        /* Calcul de la lumiere */
        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        lightDir4 = lightDir4 * ViewMatrix;
        glm::vec3 lightDir = glm::vec3(lightDir.x, lightDir.y, lightDir.z);
        
        // Shininess
        glUniform1f(cubeProgram.uShininess, cubeMat.shininess);
        glUniform3fv(cubeProgram.uKd,1, glm::value_ptr(glm::vec3(cubeMat.diffuse)));
        glUniform3fv(cubeProgram.uKs,1, glm::value_ptr(glm::vec3(cubeMat.glossy)));

        //light variables
        glUniform3fv(cubeProgram.uLightIntensity, 1, glm::value_ptr(sunLight.intensity));
        glm::vec3 tmpLightDir(glm::mat3(camera.getViewMatrix())*sunLight.direction);
        glUniform3fv(cubeProgram.uLightDir_vs, 1, glm::value_ptr(tmpLightDir));

        glBindVertexArray(cube.getVAO());
        for (int i = 0; i < maGrid.getGridSize(); ++i)
        {
            MVMatrix = glm::translate(ViewMatrix, glm::vec3(2*maGrid.getX_Grid(i), 2*maGrid.getY_Grid(i), 2*maGrid.getZ_Grid(i)));
            //MVMatrix = glm::rotate(ViewMatrix, windowManager.getTime(), glm::vec3(1, 1, 1)); //le cube bouge
            
            glUniformMatrix4fv(cubeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); // Value
            glUniformMatrix4fv(cubeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix)))); // Value
            glUniformMatrix4fv(cubeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); // Value  
            glUniform3fv(cubeProgram.uCubeColor, 1, glm::value_ptr(maGrid.getColor_Grid(i))); // Value  


            /*glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_flower);*/
                cube.drawCube();
           /* glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE0); */ 
        }

        //cursor.drawCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor(), &CubeCursorProgram, &camera);

#pragma endregion CUBE

        glBindVertexArray(0);

        above.drawAbove(WINDOW_WIDTH, WINDOW_HEIGHT, maGrid[maGrid.findCube(cursor.getX_Cursor(), cursor.getY_Cursor(), cursor.getZ_Cursor())]);
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

        above.endFrame(windowManager.m_window);

        // Update the display
        windowManager.swapBuffers();
    }

    cube.deleteBufferCube();
 
    return EXIT_SUCCESS;
}
