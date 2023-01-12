#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	return true;
}

update_status ModulePlayer::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}


// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	return UPDATE_CONTINUE;
}

