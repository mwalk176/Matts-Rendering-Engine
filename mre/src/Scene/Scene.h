#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "SceneObjects/SceneObject.h"
#include "Lights/Light.h"
#include "SceneObjects/Sphere.h"
#include "../Scene/Lights/DirectionalLight.h"
#include "../Scene/Lights/PointLight.h"
#include "../Materials/MRayTracerMat.h"

#include <vector>

class Scene {
public:
	Scene();
	Scene(std::string inputScene, Camera* inCam);
	~Scene();

	Camera* getCamera();
	std::vector<SceneObject*> getObjects();
	std::vector <Light*> getLights();

	SceneObject* getClosestObject(Ray r, double& closestPoint);

private:
	Camera* camera;
	std::vector<SceneObject*> objects;
	std::vector <Light*> lights;

	void useDefaultScene();

};

#endif