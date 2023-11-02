#include "Globals.h"
#include "AssetLoader.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Assimp/include/scene.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/postprocess.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

vector<AssetInfo*> AssetLoader::assetList;
void AssetLoader::DebugMode()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

}

void AssetLoader::LoadFile(const char* file_path, AssetInfo* ourAsset)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			// copy vertices
			ourAsset->num_vertex = scene->mMeshes[i]->mNumVertices;
			ourAsset->vertex = new float[ourAsset->num_vertex * 3];
			memcpy(ourAsset->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourAsset->num_vertex * 3);


			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				ourAsset->num_index = scene->mMeshes[i]->mNumFaces * 3;
				ourAsset->index = new uint[ourAsset->num_index]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						//App->menus->info.AddConsoleLog(__FILE__, __LINE__, "WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&ourAsset->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
				//AssetInfo::SetUpMesh(ourAsset);
				assetList.push_back(ourAsset);
			}

		}

		aiReleaseImport(scene);

	}
	else
		LOG("Error loading scene % s", file_path);
}

void AssetInfo::RenderAsset()
{
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < num_index; i++) {
		glVertex3f(vertex[index[i] * 3], vertex[index[i] * 3 + 1], vertex[index[i] * 3 + 2]);
	}

	glEnd();
}

void AssetLoader::Render()
{
	for (int i = 0; i < assetList.size(); i++) {
		assetList[i]->RenderAsset();
	}
}


void AssetLoader::CleanUp()
{

	assetList.clear();

	// detach log stream
	aiDetachAllLogStreams();
}