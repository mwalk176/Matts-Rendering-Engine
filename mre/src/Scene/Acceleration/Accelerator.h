#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include "AccelStructure.h"
#include "BruteForce.h"
#include "KDTree.h"
#include <string>

class Accelerator {
public:
	Accelerator();
	Accelerator(std::string structure);

	void init(std::vector<SceneObject*> objects);
	SceneObject* getClosestObject(Ray r, float& closestPoint);
	bool inShadow(Ray r, float& lightDist);

private:
	AccelStructure* accelStructure;

};








#endif
