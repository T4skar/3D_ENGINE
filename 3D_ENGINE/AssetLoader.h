#pragma once
#include "Module.h"
#include "Globals.h"
#include <SDL_gesture.h>


class AssetLoader : public Module
{
public:
	AssetLoader(Application* app, bool start_enabled = true);
	~AssetLoader();

	bool Init();
	update_status PostUpdate(float dt) override;
	bool CleanUp();


public:

	SDL_GLContext context;

	bool show_demo_window = false;
	bool show_credits_window = false;
	bool show_main_window = true;
	bool show_hardware_window = false;

};