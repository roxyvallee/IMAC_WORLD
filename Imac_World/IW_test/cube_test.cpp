#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <iostream>

//POUR FAIRE LA SPHERE
#include <glimac/Sphere.hpp>
#include <vector>
//POUR FAIRE LA SPHERE

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
    GLint uGrassTexture;
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
        uGrassTexture = glGetUniformLocation(m_Program.getGLId(), "uGrassTexture");
        //lumière 
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
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

    //creation de la texture du cube
    std::unique_ptr<Image> GrassTexture = loadImage("../Imac_World/assets/textures/grass.jpg");
    if(GrassTexture == nullptr){
        std::cerr << "Erreur load image " << std::endl;
    }

    FilePath applicationPath(argv[0]);
    CubeProgram cubeProgram(applicationPath);

    glEnable(GL_DEPTH_TEST);

    cubeProgram.m_Program.use();

    //background bleu
    glClearColor(0.137255f, 0.137255f, 0.556863f, 0.0f);

    //Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 0 
    //pour lire dans la texture uGrassTexture:
    glUniform1i(cubeProgram.uGrassTexture, 0);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    TrackballCamera camera;

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

    ////////////////////////////////////////////////////////////
    //POUR FAIRE UNE SPHERE
    /* 
      std::vector<glm::vec3> positions;
      for ( int i = 0; i < 32; i++ ) {
        positions.push_back(glm::sphericalRand(2.f));
      }

      glm::vec3 test = glm::sphericalRand(2.f);

      Sphere sphere(1, 32, 16);
      // Création d'un VBO
      GLuint vbo;
      glGenBuffers(1, &vbo);

      // Binding d'un VBO sur la cible GL_ARRAY_BUFFER
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

      // Débinder le VBO
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      // Spécification de sommet avec le Vertex Array Object (VAO)
      GLuint vao;
      glGenVertexArrays(1, &vao);

      // Binding du VAO
      glBindVertexArray(vao);

      // Activation des attributs de vertex
      
      glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
      
      glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);

      glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS);

      // Spécification des attributs de vertex
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glVertexAttribPointer(VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void *) 0);
      glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void *) offsetof(ShapeVertex, normal));
      glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void *) offsetof(ShapeVertex, texCoords));
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      // Debinder le VAO
      glBindVertexArray(0);
    */
    //POUR FAIRE UNE SPHERE
    ///////////////////////////////////////////////////////////

    //application de la texture de l'herbe
    GLuint texture_grass;
    glGenTextures(1, &texture_grass);
    glBindTexture(GL_TEXTURE_2D, texture_grass);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GrassTexture->getWidth(), GrassTexture->getHeight(), 0, GL_RGBA, GL_FLOAT, GrassTexture->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT :
                        camera.rotateLeft(-10.f); // la caméra bouge à gauche
                    break;
                    case SDLK_RIGHT : 
                        camera.rotateUp(10.f); // la caméra bouge vers le haut
                    case SDLK_UP :
                        camera.moveFront(1.f); // la caméra avance
                    break;
                    case SDLK_DOWN :
                        camera.moveFront(-1.f); // la caméra recule
                    break;
                }
                break;
            }
        }

        const glm::mat4 ViewMatrix = camera.getViewMatrix(); // pour placer notre caméra

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);
         
#pragma region CUBE

        cubeProgram.m_Program.use();

        glm::mat4 ModelMatrix;
        
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -5.f) ); // on recule notre caméra
        
        //Sending matrices to shaders
        glm::mat4 MVMatrix = ViewMatrix * ModelMatrix;
        const glm::mat4 NormalMatrix;

        /* Calcul de la lumiere */
        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        
        //le cube et la lumière bougent
        //MVMatrix = glm::rotate(ViewMatrix, windowManager.getTime(), glm::vec3(1, 1, 1));
        lightDir4 = lightDir4 * ViewMatrix;
        glm::vec3 lightDir = glm::vec3(lightDir.x, lightDir.y, lightDir.z);
        
        // On envoi les variables uniformes
        // Shininess
        glUniform1f(cubeProgram.uShininess, 50.0f);
        glUniform3fv(cubeProgram.uKd,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
        glUniform3fv(cubeProgram.uKs,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
        glUniform3fv(cubeProgram.uLightDir_vs, 1, glm::value_ptr(lightDir));
        //intensité de la lumière
        float cubeLi = 50.f;
        glUniform3fv(cubeProgram.uLightIntensity,1, glm::value_ptr(glm::vec3(cubeLi, cubeLi, cubeLi))); 
        
        glUniformMatrix4fv(cubeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); // Value
        glUniformMatrix4fv(cubeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix)))); // Value
        glUniformMatrix4fv(cubeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); // Value  

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_grass);
            glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
            //glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);

#pragma endregion CUBE

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);
 
    return EXIT_SUCCESS;
}
