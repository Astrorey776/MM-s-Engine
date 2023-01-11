
#pragma once


#include "glmath.h"
#include "Color.h"


class GameObject;
class ImHierarchyWindow;

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

enum class PrimitiveType
{
	PLANE,
	CUBE,
	SPHERE,
	CYLINDER,
	EMPTY,
};

class Primitive
{
public:

	Primitive();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;


	void CreatePrimitive(GameObject* p, PrimitiveType t);

public:
	

	Color color;
	mat4x4 transform;
	bool axis,wire;

protected:
	PrimitiveTypes type;
};

// ============================================
class CubeA : public Primitive
{
public :
	CubeA();
	CubeA(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
public:
	vec3 size;
};

// ============================================
class SphereA : public Primitive
{
public:
	SphereA();
	SphereA(float radius);
	void InnerRender() const;
public:
	float radius;
};

// ============================================
class CylinderA : public Primitive
{
public:
	CylinderA();
	CylinderA(float radius, float height);
	void InnerRender() const;
public:
	float radius;
	float height;
};

// ============================================
class LineA : public Primitive
{
public:
	LineA();
	LineA(float x, float y, float z);
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
