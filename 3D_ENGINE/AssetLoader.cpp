#include "Globals.h"
#include "AssetLoader.h"

#include "ImGui/imgui.h"
#include "imgui_impl_sdl2.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
void AssetLoader::DebugMode()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void AssetLoader::LoadFile(char* file_path, AssetData* ourMesh)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);

	for (size_t i = 0; i < scene->mNumMeshes; i++)
	{
		// copy vertices
		ourMesh->num_vertex = scene->mMeshes[i]->mNumVertices;
		ourMesh->vertex = new float[ourMesh->num_vertex * 3];
		memcpy(ourMesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
		LOG("New mesh with %d vertices", ourMesh->num_vertex);

		// copy faces
		if (scene->mMeshes[i]->HasFaces())
		{
			ourMesh->num_vertex = scene->mMeshes[i]->mNumFaces * 3;
			ourMesh->index = new uint[ourMesh->num_index]; // assume each face is a triangle

			for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
			{
				if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
				{
					LOG("WARNING, geometry face with != 3 indices!");
				}
				else
				{
					memcpy(&ourMesh->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
				}
			}
		}
	}
}

void AssetLoader::CreateAssetBuffer(AssetData ourMesh)
{
	glGenBuffers(1, (GLuint*)&(ourMesh.id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, ourMesh.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ourMesh.num_vertex * 3, ourMesh.vertex, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(ourMesh.id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * ourMesh.num_index, ourMesh.index, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh.id_index);
}

void AssetLoader::RenderAsset(AssetData ourMesh)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);


	glDrawElements(GL_TRIANGLES, ourMesh.num_vertex, GL_UNSIGNED_INT, NULL);

	//Move
	glPushMatrix();
	glTranslatef(-0.5, 0.5, -0.5);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
}
void AssetLoader::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
}