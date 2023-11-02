#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include "SDL_gesture.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace std;

#define VERTEX_FEATURES 5


struct AssetInfo
{

	AssetInfo() {}

	~AssetInfo() {
		delete[num_vertex]  vertex;
		delete[num_index]  index;

	}

	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	


	void RenderAsset();
};


class AssetLoader
{
public:
	void DebugMode();
	static void LoadFile(const char* file_path, AssetInfo* ourAsset);

	static void Render();
	void CleanUp();


	static vector<AssetInfo*> assetList;
};