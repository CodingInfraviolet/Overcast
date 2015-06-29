#pragma once

class Object3DInstance;

class Shape
{
	math::vec3 positionOffset; //relative to model position
};

class Sphere : public Shape
{
	float radius;
};

class PhysicsWorld;

class Physics
{
public:
	Physics(const Physics&);

	Physics();
	~Physics();
	bool initialise();
	void shutdown();
	void frame();

private:
	PhysicsWorld* world;
};


class PhysicsInstance
{
private:
	bool enabled;
	Shape* shape;
	Object3DInstance* obj;
public:
	PhysicsInstance();
	bool create(float x, float y, float z);
	void destroy();
	void enable();
	void disable();
};

class PhysicsWorld
{
	std::vector<PhysicsInstance*> objects;
};