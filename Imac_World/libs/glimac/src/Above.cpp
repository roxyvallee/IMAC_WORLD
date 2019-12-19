#include "glimac/Above.hpp"
#include <iostream>

namespace glimac {

    Above::~Above() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
    
    void Above::initImgui(SDL_Window* window, SDL_GLContext* glContext) const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();(void)io;
        ImGui_ImplSDL2_InitForOpenGL(window, &glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();
    }

    void Above::beginFrame(SDL_Window* window) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }

    void Above::drawAbove(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, ShapeGrid &cubeSelect){
        ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH-250, 10));
        ImGui::SetNextWindowSize(ImVec2(240, WINDOW_HEIGHT-(WINDOW_HEIGHT/2)));

        int changement = 0;
        clickCreateCube = 0;
        clickDeleteCube = 0;
        clickExtrudeCube = 0;
        clickDigCube = 0;

        ImGui::Begin("Tools");

        // button for create cube
        if (ImGui::Button("CREATE CUBE")){
            changement ^= 1;
            clickCreateCube++;
        }  
       
        // button for delete cube
        if (ImGui::Button("DELETE CUBE")){
            changement ^= 1;
            clickDeleteCube++;
        }  

        // button for extrude cube
        if (ImGui::Button("EXTRUDE CUBE")){
            changement ^= 1;
            clickExtrudeCube++;
        }  

        // button for dig cube
        if (ImGui::Button("DIG CUBE")){
            changement ^= 1;
            clickDigCube++;
        }  

        // buttons for change color cube
        // static float cubeColor[3] = { 0.0f, 1.0f, 0.0f };
        r = 0;
        g = 0;
        b = 0;
        if(ImGui::ColorEdit3("Cube color", (float*)cubeSelect.get_ColorPtr())){
           /* r = cubeColor[0] * 255.f;
            g = cubeColor[1] * 255.f;
            b = cubeColor[2] * 255.f;
            colorCube = glm::vec3(r, g, b);
            std::cout << "La couleur du cube est : " << colorCube << std::endl;*/
        }

        ImGui::End();
    }

    void Above::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //SDL_GL_SwapWindow(window);
    }
}


















