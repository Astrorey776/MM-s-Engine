#include "PhysBody3D.h"
#include "glmath.h"
#include "External_Libraries/Bullet/include/btBulletDynamicsCommon.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{
	is_sensor = false;
}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	delete body;
}

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
}


PhysSensor3D::PhysSensor3D(btRigidBody* body, SensorType s_type) : PhysBody3D(body)
{
	is_sensor = false;
	type = s_type;
	isEnabled = true;

	if (type == SensorType::CHECKPOINT) 
	{

		mat4x4 mat;
		body->getWorldTransform().getOpenGLMatrix(&mat);

		//ERROR LNK2019
		/*lights[0] = new CubeA(3, 3, 3);
		lights[0]->color = Red;
		lights[0]->SetPos(mat[12] + 8, mat[13] + 1.5f, mat[14]);

		lights[1] = new CubeA(3, 3, 3);
		lights[1]->color = Red;
		lights[1]->SetPos(mat[12] - 8, mat[13] + 1.5f, mat[14]);
		*/
	}
	else
	{
		//lights[0] = nullptr;
		//lights[1] = nullptr;
	}

}
PhysSensor3D::~PhysSensor3D()
{
	if (type == SensorType::CHECKPOINT) 
	{
		delete lights[0];
		delete lights[1];
	}
}

void PhysSensor3D::SetAsSensor(bool is_sensor)
{
	if (this->is_sensor != is_sensor)
	{
		this->is_sensor = is_sensor;
		if (is_sensor == true)
			body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		else
			body->setCollisionFlags(body->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

bool PhysBody3D::IsSensor()
{
	return is_sensor;
}