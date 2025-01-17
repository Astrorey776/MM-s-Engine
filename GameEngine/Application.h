#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleDummy.h"
#include "ModuleResources.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"




class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleCamera3D* camera;
	ModuleDummy* dummy;
	ModuleRenderer3D* renderer3D;
	ModuleResources* resources;
	ModulePhysics3D* physics;
	ModulePlayer* player;

private:

	Timer	ms_timer;
	float	dt;
	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();


	static Application* GetInstance();


private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	static Application* App;


};