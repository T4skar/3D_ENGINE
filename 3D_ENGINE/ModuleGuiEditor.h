#ifndef __ModuleGuiEditor_H__
#define __ModuleGuiEditor_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

class Application;

class ModuleGuiEditor : public Module
{
public:

	ModuleGuiEditor(Application* app, bool start_enabled = true);
	bool showDemo = false;
	//SDL_GLContext gl_context;
	SDL_GLContext context;
	// Destructor
	virtual ~ModuleGuiEditor();

	bool Init();

	void DrawEditor();
	//update_status PreUpdate(float dt);
	//update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool showCubeDirectMode = false;
	bool showCubeBufferColors = false;

public:
	
};

#endif // __ModuleGuiEditor_H__