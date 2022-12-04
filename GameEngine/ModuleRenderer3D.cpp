#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleDummy.h"
#include "ImGuiSamples.h"
#include "S_GameObject.h"
#include "ImHierarchyWindow.h"
#include "T_TextureLoader.h"
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"
#include "glew.h"
#include "SDL_opengl.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */


ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	
	LOG("Creating 3D Renderer context");
	bool ret = true;






	//Create context
	SDL_GLContext context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{

		LOG("Oh oh, Open gl doesn't work well :(");
		ret = false;
	}

	GLenum err = glewInit();

	SDL_GL_MakeCurrent(App->window->window, context);

	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		LOG("Error: %a\n", glewGetErrorString(err));
		LOG("HARD ERROR");
	}
	else {
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	}


	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
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
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		

		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		

		// Blend for transparency
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);

		// Enable opacity
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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
		glEnable(GL_TEXTURE_2D);


		
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);


	ImHierarchyWindow::App = this->App;
	GameObject::App = this->App;
	ImGuiSamples::App = this->App;
	ImGuiSamples::Init();


	MeshLoader::StartDebugMode();



	App->camera->sceneCamera->StartCamBuffer(SCREEN_WIDTH, SCREEN_HEIGHT);
	App->camera->gameCamera->StartCamBuffer(SCREEN_WIDTH, SCREEN_HEIGHT);

	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);



	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	App->camera->Draw();

	BindCamerBuffers(App->camera->sceneCamera);


	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();


	ImGuiSamples::NewFrame(dt);


	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{




	RenderMeshes();
	if (App->camera->gameCamera != nullptr) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		BindCamerBuffers(App->camera->gameCamera);

		RenderMeshes();

	}



	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	ImGuiSamples::Render(dt);
	SDL_GL_SwapWindow(App->window->window);
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");


	MeshLoader::StopDebugMode();
	MeshLoader::CleanUp();


	ImGuiSamples::CleanUp();
	App->camera->sceneCamera->CleanUp();

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{

	glViewport(0, 0, width, height);

}

void ModuleRenderer3D::BindCamerBuffers(CameraClass* cc)
{


	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat*)cc->GetProjectionMatrix().ptr());


	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat*)cc->GetViewMatrix().ptr());
	glBindFramebuffer(GL_FRAMEBUFFER, cc->cameraBuffer.GetFrameBuffer());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

}

void ModuleRenderer3D::RenderMeshes()
{


	for (int i = 1; i < ImGuiSamples::ImH->referenceGameObject->size(); i++) {

		GameObject* gO = ImGuiSamples::ImH->referenceGameObject->at(i);


		if (gO->mesh != nullptr && gO->name != "Root") {
			gO->RenderM();
		}
	}


}


