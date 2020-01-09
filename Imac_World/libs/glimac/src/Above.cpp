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
        ImGui_ImplSDL2_InitForOpenGL(window, &glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();
    }

    ImGuiIO Above::getIO(){
        ImGuiIO& io = ImGui::GetIO();(void)io;
        return io;
    }

    void Above::beginFrame(SDL_Window* window) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }

    void Above::drawAbove(const int WINDOW_WIDTH, const int WINDOW_HEIGHT, ShapeGrid &cubeSelect, Grid &maGrid, Cube &cube){
        ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH-250, 10));
        ImGui::SetNextWindowSize(ImVec2(240, WINDOW_HEIGHT-(WINDOW_HEIGHT/2)));

        int changement = 0;
        clickCreateCube = 0;
        clickDeleteCube = 0;
        clickExtrudeCube = 0;
        clickDigCube = 0;
        clickGenerateWorld = 0;
        clickDay = 0;
        clickNight = 0;
        clickResetAll = 0;
        clickTextureFlower = 0;
        clickTextureGrass = 0;
        clickColor = 0;

        ImGui::Begin("Menu");

        if (ImGui::BeginMenu("Tools"))
        {
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

            // button for all reset
            if (ImGui::Button("RESET")){
                changement ^= 1;
                clickResetAll++;
            }  
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Color"))
        {
            // button for change color cube
            if(ImGui::ColorEdit3("Cube color", (float*)cubeSelect.get_ColorPtr())){}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Light"))
        {
            // button for day light
            if (ImGui::Button("DAY")){
                changement ^= 1;
                clickDay++;
            } 

            static glm::vec4& dirLightX = cube.getLightD();
            static glm::vec4& pointLightX = cube.getLightP();

            //Directionnal light
            ImGui::Text("Directionnal light :");
            ImGui::Text("Coordinates D");
            ImGui::InputFloat("xD",&dirLightX.x);
            ImGui::Text("Y :");
            ImGui::InputFloat("yD", &dirLightX.y);
            ImGui::Text("Z :");
            ImGui::InputFloat("zD", &dirLightX.z);

            // button for night light
            if (ImGui::Button("NIGHT")){
                changement ^= 1;
                clickNight++;
            } 

            // Point light
            ImGui::Text("Point light :");
            ImGui::Text("Coordinates P");
            ImGui::InputFloat("xP", &pointLightX.x);
            ImGui::Text("Y :");
            ImGui::InputFloat("yP", &pointLightX.y);
            ImGui::Text("Z :");
            ImGui::InputFloat("zP", &pointLightX.z);

            GLint uLightDir_vs = cube.getULightDir();
            cube.changeDirectiveLightPosition(uLightDir_vs, dirLightX, pointLightX);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Texture"))
        {
            // button for texture flower
            if (ImGui::Button("FLOWER")){
                changement ^= 1;
                clickTextureFlower++;
            }  
            // button for texture grass
            if (ImGui::Button("GRASS")){
                changement ^= 1;
                clickTextureGrass++;
            }  
            // button for color
            if (ImGui::Button("COLOR")){
                changement ^= 1;
                clickColor++;
            }  
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("File"))
        {
            static std::string name = "scene.txt";

            ImGui::Text("Save file :");
            ImGui::InputText("Filename", &name);

            if (ImGui::Button("Save"))
            {
            	saveName = name;
                std::cout << "Votre scène a bien été enregistré" << std::endl;
            }

            if (ImGui::Button("Open"))
            {
            	openName = name;
                std::cout << "Votre scène a bien été ouverte" << std::endl;
            }
            ImGui::EndMenu();
        }

        ImGui::End();
    }

    void Above::clearString()
    {
    	saveName.clear();
    	openName.clear();
    }

    void Above::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}


















