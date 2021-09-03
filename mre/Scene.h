#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "SceneObject.h"
#include "Light.h"
#include <vector>

class Scene {
public:
	Scene();
	Scene(std::string inputScene);
	~Scene();

private:
	Camera camera;
	std::vector<SceneObject>* objects;
	std::vector <Light>* lights;

	void useDefaultScene();

};

#endif