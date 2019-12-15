#pragma once

#include <cstdint>
#include "SDL.h"
#include "glm.hpp"

namespace glimac {

class SDLWindowManager {
public:
  SDL_Window *window;

    SDLWindowManager(uint32_t width, uint32_t height, const char* title);

    ~SDLWindowManager();

    bool pollEvent(SDL_Event& e);

    bool isKeyPressed(SDL_Keycode key) const;

    // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
    bool isMouseButtonPressed(uint32_t button) const;

    glm::ivec2 getMousePosition() const;

    void swapBuffers();

    // Return the time in seconds
    float getTime() const;
};

}
