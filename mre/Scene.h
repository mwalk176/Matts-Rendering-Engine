#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "SceneObject.h"
#include "Light.h"

class Scene {
public:
	Scene();
	Scene(std::string inputScene);
	~Scene();

private:
	Camera camera;
	SceneObject* objects;
	Light* lights;

};

#endif