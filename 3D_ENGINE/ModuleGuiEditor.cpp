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
	App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Setting up the editor");
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

	// Setup ImGui style
	ImGui::StyleColorsDark();



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
		//ImGui::BeginChild("GameRender", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));
		ImVec2 wsize = ImGui::GetContentRegionAvail();

		ImGui::Image((ImTextureID)App->renderer3D->textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));
		//ImGui::EndChild();
		ImGui::End();


		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//MAIN WINDOW
		ImGui::Begin("Main", NULL, ImGuiWindowFlags_MenuBar);

		//Menus
		if (ImGui::BeginMenuBar())
		{
			//if (ImGui::BeginMenu("Main"))
			//{
			//	ImGui::EndMenu();
			//}
			if (ImGui::BeginMenu("Info"))
			{

				if (ImGui::MenuItem("Documentation"))
				{
					ShellExecuteA(NULL, "open", "https://github.com/T4skar/3D_ENGINE/wiki", NULL, NULL, SW_SHOWDEFAULT);
				}
				if (ImGui::MenuItem("Download Latest"))
				{
					ShellExecuteA(NULL, "open", "https://github.com/T4skar/3D_ENGINE/releases", NULL, NULL, SW_SHOWDEFAULT);
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
			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Console"))
				{
					show_console_window = true;
					console_visible = !console_visible;

				}
				if (ImGui::MenuItem("Hierarchy"))
				{
					show_hierarchy_window = true;
					hierarchy_visible = !hierarchy_visible;

				}
				if (ImGui::MenuItem("Inspector"))
				{
					show_inspector_window = true;
					inspector_visible = !inspector_visible;
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Exit"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					show_main_window = false;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		//Main Window
		ImGui::Text("Basic Geometric Forms:\n");

		if (ImGui::Button("Cube"))
		{
			//Load basic geometry
		}
		ImGui::SameLine();
		if (ImGui::Button("Cone"))
		{
			//Load basic geometry
		}
		ImGui::SameLine();
		if (ImGui::Button("Sphere"))
		{
			//Load basic geometry
		}
		ImGui::SameLine();
		if (ImGui::Button("BeaconHouse"))
		{
			//Load basic geometry
		}

		
		ImGui::Text("\n\n");

		
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
		ImGui::Text("3DENGINE\n\n");
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

		ImGui::Text("MIT License\n\nCopyright(c) 2023 T4skar & AdriRamirez\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the Software), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions :\n\n");
		ImGui::Text("The above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\n");
		ImGui::Text("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");

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
	//CONSOLE WINDOW
	if (console_visible)
	{
		ShowConsoleWindow();
	}


	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//HIERARCHY WINDOW
	if (hierarchy_visible) 
	{
		if (show_hierarchy_window)
		{
			ImGui::Begin("Hierarchy", &show_hierarchy_window, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
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
			ImGui::Text("GameObjects: \n");
	

			ImGui::End();
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//INSPECTOR WINDOW
	if (inspector_visible) 
	{
		if (show_inspector_window)
		{
			ImGui::Begin("Inspector", &show_inspector_window, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);


			if (ImGui::CollapsingHeader("FRAMERATE"))
			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				char title[25];
				sprintf_s(title, 25, "Framerate %1.f", fpsLog[fpsLog.size() - 1]);
				ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
				sprintf_s(title, 25, "Milliseconds %0.f", timeLog[timeLog.size() - 1]);
				ImGui::PlotHistogram("##milliseconds", &timeLog[0], timeLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			}

			if (ImGui::CollapsingHeader("Options"))
			{
				ImGui::Text("Render Settings:\n");
				ImGui::Checkbox("Wireframe Mode", &wireframe);
				ImGui::SameLine();
				ImGui::Checkbox("Lights", &App->renderer3D->lights_active);

				ImGui::Checkbox("Depth Test", &App->renderer3D->depth_test_active);
				ImGui::SameLine();
				ImGui::Checkbox("Culling Face", &App->renderer3D->cull_face_active);
				ImGui::Text("\n");
			}


			ImGui::End();
		}
	}

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

void ModuleGuiEditor::ShowConsoleWindow()
{
	if (show_console_window)
	{
		consoleWindow.Draw("Console", &show_console_window);

	}
	if (show_console_window == NULL)
	{
		console_visible = !console_visible;
	}
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