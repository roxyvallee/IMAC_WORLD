#include "glimac/SDLWindowManager.hpp"
#include <iostream>
#include <GL/gl.h>

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    SDL_GLContext openglContext = SDL_GL_CreateContext (window);

    std::cout <<  glGetString (GL_VERSION) << std::endl;

    if(!window) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }
}

SDLWindowManager::~SDLWindowManager() {
    SDL_Quit();
}

bool SDLWindowManager::pollEvent(SDL_Event& e) {
    return SDL_PollEvent(&e);
}

bool SDLWindowManager::isKeyPressed(SDL_Keycode key) const {
    return SDL_GetKeyboardState(nullptr)[key];
}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const {
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}

