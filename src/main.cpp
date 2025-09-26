#include "headers.hpp"

int main ()
{
    glfw::init ();
    world::init ();
    points::init ();

    IMGUI_CHECKVERSION ();

    ImGui::CreateContext ();
    ImGui::StyleColorsDark ();

    ImGui_ImplGlfw_InitForOpenGL (glfw::window, true);
    ImGui_ImplOpenGL3_Init ("#version 330");
    
    while (glfwWindowShouldClose (glfw::window) == 0)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor (0.85f, 0.85f, 0.85f, 1.0f);
        
        points::draw (camera::getProjectionMatrix (), camera::getViewMatrix ());
        world::draw (camera::getProjectionMatrix (), camera::getViewMatrix ());
        
        ImGui_ImplGlfw_NewFrame ();
        ImGui_ImplOpenGL3_NewFrame ();
        ImGui::NewFrame ();

// ========== PRIMARY UI SETTINGS AND RENDERING ========== //
        {
            float uiWidth = static_cast <float>(glfw::windowWidth) * 0.25f;
    
            ImGui::SetNextWindowPos (ImVec2 (static_cast<float>(glfw::windowWidth) - uiWidth, 0.0f), ImGuiCond_Always);
            ImGui::SetNextWindowSize (ImVec2 (uiWidth, static_cast<float>(glfw::windowHeight) * 0.25f), ImGuiCond_Always);

            ImGui::Begin ("RENDERING BIVARIATE FUNCTIONS WITH OPENGL", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    
            ImGui::InputText ("f (x, z)", buf, IM_ARRAYSIZE (buf));
    
            if (ImGui::Button ("Set new function"))
            {
                points::setNewFunctionGraph (std::string (buf));
            }
    
            ImGui::Checkbox ("Animate function", &points::isAnimating);
    
            ImGui::End ();
        }

// ========== SECONDARY UI SETTINGS AND RENDERING ========== //

        {
            ImGui::SetNextWindowPos (ImVec2 (10.0f, 10.0f), ImGuiCond_Always);
            ImGui::SetNextWindowSize (ImVec2 (150.0f, 50.0f), ImGuiCond_Always);

            ImGui::Begin ("QPS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);

            ImGui::TextColored (ImVec4 (0.0f, 0.0f, 0.0f, 1.0f) ,"%.1f", ImGui::GetIO ().Framerate);

            ImGui::End ();
        }

        ImGui::Render ();
        ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());

        glfwPollEvents ();
        glfwSwapBuffers (glfw::window);
    }

    ImGui_ImplOpenGL3_Shutdown ();
    ImGui_ImplGlfw_Shutdown ();
    ImGui::DestroyContext ();

    points::terminate ();
    world::terminate ();
    glfw::terminate ();
}