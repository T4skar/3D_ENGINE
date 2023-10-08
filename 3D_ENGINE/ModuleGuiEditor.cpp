#include "Globals.h"
#include "Application.h"
#include "ModuleGuiEditor.h"

ModuleGuiEditor::ModuleGuiEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleGuiEditor::~ModuleGuiEditor()
{
}

// Called before render is available
bool ModuleGuiEditor::Init()
{
	LOG("Init Gui Editor");
	bool ret = true;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
  //  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
  //  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();


	return ret;
}

update_status ModuleGuiEditor::PostUpdate(float dt)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        ImGui::ShowDemoWindow();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;
        
        ImGui::Begin("Hello, world!", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);       // Create a window called "Hello, world!" and append into it.
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Gui Demo"))
                    showDemo = !showDemo;

                if (ImGui::MenuItem("Documentation"))
                    ShellExecuteA(NULL, "open", "https://github.com/d0n3val/Edu-Game-Engine/wiki", NULL, NULL, SW_SHOWDEFAULT);

                if (ImGui::MenuItem("Download latest"))
                    ShellExecuteA(NULL, "open", "https://github.com/d0n3val/Edu-Game-Engine/releases", NULL, NULL, SW_SHOWDEFAULT);

                if (ImGui::MenuItem("Report a bug"))
                    ShellExecuteA(NULL, "open", "https://github.com/d0n3val/Edu-Game-Engine/issues", NULL, NULL, SW_SHOWDEFAULT);

                if (ImGui::MenuItem("About"))
                    ShellExecuteA(NULL, "open", "https://learnopengl.com/", NULL, NULL, SW_SHOWDEFAULT);

                if (ImGui::MenuItem("Support"))
                    ShellExecuteA(NULL, "open", "https://www.youtube.com/watch?v=2C4lFUpI_4U", NULL, NULL, SW_SHOWDEFAULT);

                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //ImGui::Checkbox("Demo Window");      // Edit bools storing our window open/close state
        //ImGui::Checkbox("Another Window");

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (showDemo) {
        ImGui::Begin("Another Window", &showDemo);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        ImGui::End();
    }
        
    

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleGuiEditor::CleanUp()
{
	LOG("Destroying ImGui Editor");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
	
	return true;
}

