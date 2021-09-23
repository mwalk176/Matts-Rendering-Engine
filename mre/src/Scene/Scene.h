#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"

#include "SceneObjects/SceneObject.h"
#include "SceneObjects/Sphere.h"
#include "SceneObjects/Rectangle.h"
#include "SceneObjects/Triangle.h"

#include "Lights/Light.h"
#include "../Scene/Lights/DirectionalLight.h"
#include "../Scene/Lights/PointLight.h"

#include "../Materials/MRayTracerMat.h"
#include "../Materials/MPathTracerMat.h"

#include <vector>

class Scene {
public:
	Scene();
	Scene(std::string inputScene, Camera* inCam);
	~Scene();

	Camera* getCamera();
	std::vector<SceneObject*> getObjects();
	std::vector <Light*> getLights();
	Vec3 getBackgroundColor();

	SceneObject* getClosestObject(Ray r, double& closestPoint);
	SceneObject* getShadowObject(Ray r, double& closestPoint, double& lightDist);

private:
	Camera* camera;
	std::vector<SceneObject*> objects;
	std::vector <Light*> lights;
	Vec3 backgroundColor;

	void useDefaultScene();

};

#endif