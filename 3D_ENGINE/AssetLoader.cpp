#include "Globals.h"
#include "Application.h"
#include "AssetLoader.h"
#include "SDL\include\SDL_opengl.h"


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include "SDL/include/SDL_opengl.h"
#endif

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

AssetLoader::AssetLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
AssetLoader::~AssetLoader()
{}

// Called before render is available
bool AssetLoader::Init()
{
	bool ret = true;



	return ret;
}


// PostUpdate present buffer to screen
update_status AssetLoader::PostUpdate(float dt)
{



	return UPDATE_CONTINUE;
}

// Called before quitting
bool AssetLoader::CleanUp()
{
	LOG("");

	// Cleanup

	return true;
}