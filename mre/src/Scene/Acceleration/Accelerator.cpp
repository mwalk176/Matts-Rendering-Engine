#include "Accelerator.h"

Accelerator::Accelerator() {
	accelStructure = new BruteForce();
}

Accelerator::Accelerator(std::string structure) {
	if (structure == "BRUTEFORCE") accelStructure = new BruteForce();
	if (structure == "KDTREE") accelStructure = new KDTree();
	else accelStructure = new BruteForce();

}

void Accelerator::init(std::vector<SceneObject*> objects) {
	accelStructure->buildTree(objects);
}

SceneObject* Accelerator::getClosestObject(Ray r, float& closestPoint) {
	return accelStructure->traverseTree(r, closestPoint);
}

bool Accelerator::inShadow(Ray r, float& lightDist) {
	return accelStructure->findFirstIntersction(r, lightDist);
}
