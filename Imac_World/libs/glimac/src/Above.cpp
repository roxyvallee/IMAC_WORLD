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
        clickGenerateWorld = 0;
        clickSaveFile = 0;
        clickOpenFile = 0;

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

        // button for generate world
        if (ImGui::Button("GENERATE WORLD")){
            changement ^= 1;
            clickGenerateWorld++;
        }  

        // button for change color cube
        if(ImGui::ColorEdit3("Cube color", (float*)cubeSelect.get_ColorPtr())){}

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) 
            { 
                changement ^= 1; 
                clickOpenFile++;
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   
            { 
                changement ^= 1; 
                clickSaveFile++;
            }
            ImGui::EndMenu();
        }

        ImGui::End();
    }

    void Above::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //SDL_GL_SwapWindow(window);
    }
}


















