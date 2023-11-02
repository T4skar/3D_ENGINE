#ifndef __ModuleGuiEditor_H__
#define __ModuleGuiEditor_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_opengl.h"
#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

struct ConsoleWindow
{
	//Parameters
	ImGuiTextBuffer Buffer;
	ImGuiTextFilter Filter;
	ImVector<int> Vector;

	bool ScrollToBottom;

	//Functions
	void Clear()
	{
		Buffer.clear();
		Vector.clear();
	}

	void AddLog(const char file[], int line, const char* text, ...)
	{
		static char tmp_string[4096];
		static char tmp_string2[4096];
		static va_list  ap;

		va_start(ap, text);
		vsprintf_s(tmp_string, 4096, text, ap);

		va_end(ap);
		sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);

		OutputDebugString(tmp_string2);

		int old_size = Buffer.size();
		va_list args;

		va_start(args, text);
		Buffer.appendfv(text, args);
		Buffer.appendfv("\n", args);

		va_end(args);

		for (int new_size = Buffer.size(); old_size < new_size; old_size++)
		{
			if (Buffer[old_size] == '\n')
			{
				Vector.push_back(old_size);
			}
		}
		ScrollToBottom = true;
	}

	void Draw(const char* title, bool* p_opened = NULL)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 400));
		ImGui::Begin(title, p_opened);

		if (ImGui::Button("Clear"))
		{
			Clear();
		}


		ImGui::BeginChild("scrolling");
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));

		

		ImGui::TextUnformatted(Buffer.begin());

		if (ScrollToBottom)
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ScrollToBottom = false;

		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::End();
	}
};

class ModuleGuiEditor : public Module
{
public:

	ModuleGuiEditor(Application* app, bool start_enabled = true);
	virtual ~ModuleGuiEditor(); 	// Destructor

	SDL_GLContext gl_context;
	ConsoleWindow consoleWindow;

	bool Init();

	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void ShowConsoleWindow();
	

	void PushLog(std::vector<float>* Log, float toPush);

	const char* house_filepath = "Assets/BakerHouse.fbx";
	AssetInfo houseAsset;

	const char* cube_filepath = "Assets/cube.fbx";
	AssetInfo cubeAsset;

	const char* cone_filepath = "Assets/cone.fbx";
	AssetInfo coneAsset;

	const char* sphere_filepath = "Assets/sphere.fbx";
	AssetInfo sphereAsset;
	
	bool show_main_window = true;
	bool show_hardware_window = false;
	bool show_credits_window = false;
	bool show_console_window = true;
	bool show_hierarchy_window = true;
	bool show_inspector_window = true;

	bool console_visible = true;
	bool hierarchy_visible = true;
	bool inspector_visible = true;

	bool wireframe = false;

	std::vector<float> fpsLog;
	std::vector<float> timeLog;

public:
	
};

#endif // __ModuleGuiEditor_H__