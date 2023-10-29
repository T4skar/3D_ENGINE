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

update_status ModuleGuiEditor::Update(float dt)
{
    float FPS = floorf(App->GetFrameRate());
    float MS = (App->GetDt() * 1000.f);

    PushLog(&fpsLog, FPS);
    PushLog(&timeLog, MS);

    return UPDATE_CONTINUE;
}


update_status ModuleGuiEditor::PostUpdate(float dt)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("BackGround Window", nullptr, windowFlags);

    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceId = ImGui::GetID("BackGroundWindowDockSpace");

    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();

	if (show_main_window)
	{
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//SCREEN
		ImGui::Begin("GameRender", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar);
		ImVec2 wsize = ImGui::GetWindowSize();

		float w = ImGui::GetContentRegionAvail().x;
		float h = w * (9.0f / 16.0f);
		
		ImGui::End();


		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//MAIN WINDOW
		ImGui::Begin("Main", NULL, ImGuiWindowFlags_MenuBar);

		//Menus
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Main"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Info"))
			{

				if (ImGui::MenuItem("Documentation"))
				{
					//Meter el github
				}
				
				if (ImGui::MenuItem("Hardware"))
				{
					show_hardware_window = true;
				}
				if (ImGui::MenuItem("About"))
				{
					show_credits_window = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View"))
			{
				
			}

			if (ImGui::BeginMenu("Exit"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					show_main_window = false;                     //See ModuleImput 121
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		//Main Window
		ImGui::Text("Basic Geometric Forms:\n");
		
        //Aqui meter las formas basicas

		ImGui::Text("\n");

		ImGui::Text("Render Settings:\n");
		
		ImGui::Text("\n\n");

		if (ImGui::CollapsingHeader("FRAMERATE"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			char title[25];
			sprintf_s(title, 25, "Framerate %1.f", fpsLog[fpsLog.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.f", timeLog[timeLog.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &timeLog[0], timeLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		}
		ImGui::End();
	}


	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//ABOUT WINDOW

	if (show_credits_window)
	{
		ImGui::Begin("About", &show_credits_window, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Settings"))
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("Motor3D\n\n");
		ImGui::Text("External Libraries:");
		if (ImGui::Button("ImGui 1.88")) {

			::ShellExecuteA(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		if (ImGui::Button("MathGeoLib 2016")) {

			::ShellExecuteA(NULL, "open", "https://github.com/juj/MathGeoLib", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		if (ImGui::Button("Assimp")) {

			::ShellExecuteA(NULL, "open", "https://github.com/assimp/assimp", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		if (ImGui::Button("DevIL")) {

			::ShellExecuteA(NULL, "open", "https://github.com/DentonW/DevIL", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		ImGui::Text("\n\n");
		if (ImGui::Button("Glew 2.1.0.0")) {

			::ShellExecuteA(NULL, "open", "https://github.com/nigels-com/glew", NULL, NULL, SW_SHOWDEFAULT);
		}
		

		ImGui::Text("\n\n");

		//Aqui va el copirrigt y las licencias y toda la pesca

		ImGui::End();
	}


	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//HARDWARE WINDOW
	if (show_hardware_window)
	{
		ImGui::Begin("Hardware", &show_hardware_window, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Settings"))
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("SDL Version: 2.0.4\n");
		ImGui::Text("CPU's: %d", SDL_GetCPUCount());
		ImGui::Text("RAM: %d", SDL_GetSystemRAM());

		ImGui::Text("\n\n");

		ImGui::End();
	}







	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//DEMO WINDOW
		// 
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


void ModuleGuiEditor::PushLog(std::vector<float>* Log, float toPush)
{

	if (Log->size() > 100)
	{
		Log->erase(Log->begin());
		Log->push_back(toPush);
	}
	else Log->push_back(toPush);


}