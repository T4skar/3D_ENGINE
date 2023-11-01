#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL_gesture.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class aiAsset;

struct AssetData
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};


namespace AssetLoader
{
	void DebugMode();
	void LoadFile(char* file_path, AssetData* ourMesh);
	void CreateAssetBuffer(AssetData ourMesh);
	void RenderAsset(AssetData ourMesh);
	void CleanUp();
}