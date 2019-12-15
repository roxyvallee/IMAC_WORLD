#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Cube.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <iostream>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }



    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + argv[1],
                                    applicationPath.dirPath() + argv[2]);
    program.use();
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    GLint locationMVP = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    if (locationMVP == -1)
    {
        std::cerr << "Unable to find uMVPMatrix in " << (applicationPath.dirPath() + argv[1]) << " or " << (applicationPath.dirPath() + argv[2]) << std::endl;
        return EXIT_FAILURE;
    }

     GLint locationMV = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    if (locationMV == -1)
    {
        std::cerr << "Unable to find uMVMatrix in " << (applicationPath.dirPath() + argv[1]) << " or " << (applicationPath.dirPath() + argv[2]) << std::endl;
        //return EXIT_FAILURE;
    }

     GLint locationNormal = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    if (locationNormal == -1)
    {
        std::cerr << "Unable to find uNormalMatrix in " << (applicationPath.dirPath() + argv[1]) << " or " << (applicationPath.dirPath() + argv[2]) << std::endl;
        return EXIT_FAILURE;
    }
    /*
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    TrackballCamera camera;

    const glm::mat4 ProjMatrix = glm::perspective( glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    //glm::mat4 MVMatrix; //on les appelle plus tard dans le rendering code
    //glm::mat4 NormalMatrix;

    //MVMatrix = glm::translate(MVMatrix, glm::vec3(0.f, 0.f, -5.f) );
    //NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    Cube cube;
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);     

     const GLuint VERTEX_ATTRIB_POSITION = 0;
     const GLuint VERTEX_ATTRIB_NORMAL = 1;
     const GLuint VERTEX_ATTRIB_TEXCOORDS = 2;

     glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
     glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
     glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS);

     glBindBuffer(GL_ARRAY_BUFFER, vbo);
     glVertexAttribPointer(VERTEX_ATTRIB_POSITION,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, position)));
     glVertexAttribPointer(VERTEX_ATTRIB_NORMAL,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, normal)));
     glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS,2,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex), (const GLvoid*) (offsetof(ShapeVertex, texCoords)));

     glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);


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
         

        glm::mat4 ModelMatrix;
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -5.f) ); // on recule notre caméra
        //Sending matrices to shaders
        const glm::mat4 MVMatrix = ViewMatrix * ModelMatrix;
        const glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(locationMVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(locationMV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(locationNormal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

        glBindVertexArray(0);

     
        // Update the display
        windowManager.swapBuffers();
    }

 

    return EXIT_SUCCESS;
}
