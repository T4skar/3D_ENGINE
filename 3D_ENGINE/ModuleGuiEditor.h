#ifndef __ModuleGuiEditor_H__
#define __ModuleGuiEditor_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_opengl.h"
#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

class Application;

class ModuleGuiEditor : public Module
{
public:

	ModuleGuiEditor(Application* app, bool start_enabled = true);
	bool showDemo = false;
	SDL_GLContext gl_context;
	// Destructor
	virtual ~ModuleGuiEditor();

	bool Init();
	//update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	

	void PushLog(std::vector<float>* Log, float toPush);



	
	bool show_main_window = true;
	bool show_hardware_window = false;
	bool show_credits_window = false;
	bool console_visible = true;

	std::vector<float> fpsLog;
	std::vector<float> timeLog;

public:
	
};

#endif // __ModuleGuiEditor_H__