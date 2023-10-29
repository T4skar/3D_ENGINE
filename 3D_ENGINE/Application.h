#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGuiEditor.h"
#include "AssetLoader.h"

#include<vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleGuiEditor* editor;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	AssetLoader* assetloader;
	

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();


	//To get Delta time and FrameRate
	float GetDt() const { return dt; }
	float GetFrameRate()const { return 1.f / dt; }


private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};