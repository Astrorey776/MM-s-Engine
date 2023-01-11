#include "Application.h"
#include "Globals.h"
#include "ModulePhysics.h"

#ifdef _DEBUG
#pragma comment (lib, "External_Libraries/Bullet/libx86/BulletDynamics_debug.lib")
#pragma comment (lib, "External_Libraries/Bullet/libx86/BulletCollision_debug.lib")
#pragma comment (lib, "External_Libraries/Bullet/libx86/LinearMath_debug.lib")
#else
#pragma comment (lib, "External_Libraries/Bullet/libx86/BulletDynamics.lib")
#pragma comment (lib, "External_Libraries/Bullet/libx86/BulletCollision.lib")
#pragma comment (lib, "External_Libraries/Bullet/libx86/LinearMath.lib")
#endif

ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = false;

	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	//Error ambiguo
	//debug_draw = new DebugDrawer();
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	delete debug_draw;
	delete solver;
	delete broad_phase;
	delete dispatcher;
	delete collision_conf;
}

// Render not available yet----------------------------------
bool ModulePhysics3D::Init()
{
	LOG("Creating 3D Physics simulation");
	bool ret = true;

	return ret;
}

bool ModulePhysics3D::Start()
{
	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	return true;
}