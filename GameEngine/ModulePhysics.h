#pragma once
#pragma once

#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "External_Libraries/Bullet/include/btBulletDynamicsCommon.h"
#include <list>
#include <map>

#define GRAVITY btVector3(0.0f, -10.0f, 0.0f) 

class DebugDrawer;
struct PhysBody3D;
struct PhysVehicle3D;
struct VehicleInfo;


class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	//PhysBody3D* AddBody(const Sphere& sphere, float mass = 1.0f);
	PhysBody3D* AddBody(const Cube& cube, float mass = 1.0f);
	//PhysBody3D* AddBody(const Cylinder& cylinder, float mass = 1.0f);
	//PhysSensor3D* AddSensor(const Cube& cube, const vec3, const SensorType, vec4);
	PhysVehicle3D* AddVehicle(const VehicleInfo& info);
	PhysVehicle3D* GetVehicle(int);

	btTypedConstraint* AddConstraintP2P(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB);
	btHingeConstraint* AddConstraintHinge(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec3& anchorA, const vec3& anchorB, const vec3& axisS, const vec3& axisB, bool disable_collision = false);
	btFixedConstraint* AddFixedConstrain(PhysBody3D& bodyA, PhysBody3D& bodyB, btVector3 offset);
	btFixedConstraint* AddFixedConstrain(btRigidBody& bodyA, PhysBody3D& bodyB, btVector3 offset);
	void SetGravity(const vec3 v);
	btVector3 GetGravity();
	//void ChangeGravityBySensor(PhysSensor3D* sensor);

private:

	bool debug;

	btDefaultCollisionConfiguration* collision_conf;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* broad_phase;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* world;
	btDefaultVehicleRaycaster* vehicle_raycaster;
	DebugDrawer* debug_draw;

	p2List<btCollisionShape*> shapes;
	p2List<PhysBody3D*> bodies;
	p2List<btDefaultMotionState*> motions;
	p2List<btTypedConstraint*> constraints;
	p2List<PhysVehicle3D*> vehicles;
};