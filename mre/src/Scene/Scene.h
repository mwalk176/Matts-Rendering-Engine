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

#include "Acceleration/Accelerator.h"

#include "../Image/Image.h"

#include <vector>

class Scene {
public:
	Scene();
	Scene(std::string inputScene, Camera* inCam, std::string accelMethod);
	~Scene();

	Camera* getCamera();
	std::vector<SceneObject*> getObjects();
	//std::vector<SceneObject*> getObjectLights();
	std::vector <Light*> getLights();
	Vec3 getBackgroundColor();

	SceneObject* getClosestObject(Ray r, float& closestPoint);
	bool inShadow(Ray r, float& lightDist);

private:
	Camera* camera;
	std::vector<SceneObject*> objects;
	//std::vector<SceneObject*> objectLights;
	std::vector <Light*> lights;
	Vec3 backgroundColor;
	Accelerator accelerator;
	

	void useDefaultScene();
	void scene1();
	//void computeObjectLights();

};

#endif