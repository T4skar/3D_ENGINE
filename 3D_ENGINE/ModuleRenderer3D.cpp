#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "AssetLoader.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "glu32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib")

#ifdef _DEBUG
#pragma comment (lib, "MathGeoLib/libx86/_Debug/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#else
#pragma comment (lib, "MathGeoLib/libx86/_Release/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#endif // _DEBUG


ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer");
	App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Creating 3D Renderer");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	//GLEW                       
	GLenum err = glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Initializing Glew");
	

	SDL_GL_MakeCurrent(App->window->window, context);

	if(ret == true)
	{
		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0) {
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
			App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Warning: Unable to set VSync!");
		}
		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Error initializing OpenGL!");
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Error initializing OpenGL!");
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			App->editor->consoleWindow.AddLog(__FILE__, __LINE__, "Error initializing OpenGL!");
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Grid.axis = true;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//FRAMEBUFFER
	InitFrameBuffer();

	//Mesh Buffer
	AssetLoader::LoadFile(house_filepath, &houseAsset);



	//glGenBuffers(1, &vboId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals) + sizeof(colors), 0, GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);                             // copy vertices starting from 0 offest
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);                // copy normals after vertices
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);  // copy colours after normals
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &iboId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, context);
	ImGui_ImplOpenGL3_Init("#version 130");

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();


	//Cube
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	//FRAMEBUFFER
	glBindFramebuffer(GL_FRAMEBUFFER, textureColorbuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{

	AssetLoader::Render();

	//Wireframe mode
	if (App->editor->wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Enable/Disable lights
	if (lights_active == false)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);

	//Enable/Disable depth test
	if (depth_test_active == false)
		glDisable(GL_DEPTH_TEST);
	else
		glEnable(GL_DEPTH_TEST);

	//Enable/Disable cull face
	if (cull_face_active == false)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	//// enable vertex arrays
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_VERTEX_ARRAY);

	//// before draw, specify vertex and index arrays with their offsets
	//glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
	//glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	//glVertexPointer(3, GL_FLOAT, 0, 0);

	//glDrawElements(GL_TRIANGLES,            // primitive type
	//	36,                      // # of indices
	//	GL_UNSIGNED_INT,         // data type
	//	(void*)0);               // ptr to indices

	//glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);

	//// it is good idea to release VBOs with ID 0 after use.
	//// Once bound with 0, all pointers in gl*Pointer() behave as real
	//// pointer, so, normal vertex array operations are re-activated
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//FRAMEBUFFER
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(ProjectionMatrix.M);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::InitFrameBuffer()
{


	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// generate texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// create render buffer object
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720); //Size of the screen printed
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
}

void ModuleRenderer3D::RefreshBuffer()
{
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteTextures(1, &textureColorbuffer);
	glDeleteRenderbuffers(1, &renderbuffer);

	InitFrameBuffer();
}