#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
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

    CubeProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl", applicationPath.dirPath() + "shaders/directionallight.fs.glsl")){
        //texture
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
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
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForOpenGL(windowManager.m_window, &windowManager.m_glContext);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();

    //création de la lumière et des matériaux
    Light sunLight(glm::vec3(1.777,1.777,1.777), glm::vec3(1,1,1));
    Material cubeMat(glm::vec3(0.7,0.7,0.7), glm::vec3 (0.3,0.3,0.3), 10);

    //création de la texture du cube
    std::unique_ptr<Image> GrassTexture = loadImage("../Imac_World/assets/textures/flower.jpg");
    if(GrassTexture == nullptr){
        std::cerr << "Erreur load image " << std::endl;
    }

    FilePath applicationPath(argv[0]);
    CubeProgram cubeProgram(applicationPath);

    glEnable(GL_DEPTH_TEST);

    cubeProgram.m_Program.use();

    //Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 0 
    //pour lire dans la texture uTexture:
    glUniform1i(cubeProgram.uTexture, 0);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    FreeflyCamera camera;

    const glm::mat4 ProjMatrix = glm::perspective( glm::radians(70.f), WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.f);

    /////////////////////////////////////////////////////////////
    //POUR FAIRE UN CUBE
    Cube cube;
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);     

        glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(VERTEX_ATTRIB_POSITION,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, position)));
            glVertexAttribPointer(VERTEX_ATTRIB_NORMAL,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, normal)));
            glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS,2,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, texCoords)));
        glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);
    //POUR FAIRE UN CUBE
    ////////////////////////////////////////////////////////////

    //application de la texture de l'herbe
    GLuint texture_grass;
    glGenTextures(1, &texture_grass);
    glBindTexture(GL_TEXTURE_2D, texture_grass);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GrassTexture->getWidth(), GrassTexture->getHeight(), 0, GL_RGBA, GL_FLOAT, GrassTexture->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

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
                if (e.key.keysym.sym=='z'){ //up
                    camera.moveFront(1);
                }
                 if (e.key.keysym.sym=='s'){ //down
                    camera.moveFront(-1);
                }
                if (e.key.keysym.sym=='q'){ //up
                    camera.moveLeft(1);
                }
                 if (e.key.keysym.sym=='d'){ //down
                    camera.moveLeft(-1);
                }
                break;

            case SDL_KEYUP:
                //std::cout << "touche levée (code = "<< e.key.keysym.sym << ")" << std::endl;
                break;
            }
        }

        const glm::mat4 ViewMatrix = camera.getViewMatrix(); // pour placer notre caméra

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClearColor(0.439216f, 0.576471f, 0.858824f, 0.0f); //background bleu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///////IMGUI/////////
        ////////////////////

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(windowManager.m_window);
        ImGui::NewFrame();

        ///////IMGUI/////////
        ////////////////////

        glBindVertexArray(vao);
         
#pragma region CUBE

        cubeProgram.m_Program.use();

        glm::mat4 ModelMatrix;
        const glm::mat4 NormalMatrix;
        glm::mat4 MVMatrix = camera.getViewMatrix();
        //glm::mat4 MVMatrix = ViewMatrix * ModelMatrix;
       // ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -5.f) ); // on recule notre caméra

        /* Calcul de la lumiere */
        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        //MVMatrix = glm::rotate(ViewMatrix, windowManager.getTime(), glm::vec3(1, 1, 1)); //le cube bouge
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
        
        glUniformMatrix4fv(cubeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); // Value
        glUniformMatrix4fv(cubeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix)))); // Value
        glUniformMatrix4fv(cubeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); // Value  

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_grass);
            glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);

#pragma endregion CUBE

        glBindVertexArray(0);

        ///////IMGUI/////////
        ////////////////////

        ImGui::Begin("demo");
        ImGui::Button("hello");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
       // SDL_GL_SwapWindow(windowManager.m_window);

        ///////IMGUI/////////
        ////////////////////

        // Update the display
        windowManager.swapBuffers();
    }

    // Cleanup imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);

    SDL_GL_DeleteContext(windowManager.m_glContext);
    SDL_DestroyWindow(windowManager.m_window);
    SDL_Quit();
 
    return EXIT_SUCCESS;
}
