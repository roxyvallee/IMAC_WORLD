#include "glimac/Overlay.hpp"
#include <iostream>

namespace glimac {

    Overlay::~Overlay() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Overlay::initImgui(SDL_Window* window,SDL_GLContext* glContext) const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        ImGui_ImplSDL2_InitForOpenGL(window,&glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();
    }

    void Overlay::beginFrame(SDL_Window* window) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }

    void Overlay::drawOverlay() const {
        ImGui::Begin("WorldIMaker tools");
        {
            int show = 1;
            static int clicked = 0;
            if (ImGui::Button("Add cube")) {
                show ^= 1;
                clicked++;
            }
            if(clicked &1) {
                ImGui::SameLine();
                ImGui::Text("Thanks for clicking me!");
            }
            if (ImGui::Button("Add texture")) 
            {
                show ^= 1;
            }
            if (ImGui::Button("Destroy cube")) 
            { 
                show ^= 1;
            }
            if (ImGui::Button("Save"))
            {
                show ^= 1;
            }
        }
        ImGui::End();
    }

    void Overlay::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}
