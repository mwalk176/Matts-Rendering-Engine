#include "BruteForce.h"

void BruteForce::buildTree(std::vector<SceneObject*> objects) {
	for (int i = 0; i < objects.size(); i++) {
		BoundingBox* box = new BoundingBox(objects.at(i));
		std::cout << *box << std::endl;
		boxList.push_back(box);
	}
}

SceneObject* BruteForce::traverseTree(Ray r, float& closestPoint) {
	int closestObject = -1;
	float p0 = INFINITY;
	float p1 = INFINITY;

	for (int i = 0; i < boxList.size(); i++) {
		if (boxList[i]->intersect(r)) {
			SceneObject* o = boxList[i]->obj;
			if (o->intersect(r, p0, p1)) {
				if (p0 < closestPoint) {
					closestPoint = p0;
					closestObject = i;
				} else {
					continue;
				}
			}
		}
	}

	if (closestObject != -1) return boxList[closestObject]->obj;
	else return nullptr;
}

bool BruteForce::findFirstIntersection(Ray r, float& lightDist) {
	int closestObject = -1;
	float p0 = INFINITY;
	float p1 = INFINITY;

	for (int i = 0; i < boxList.size(); i++) {
		if (boxList[i]->intersect(r)) {
			SceneObject* o = boxList[i]->obj;
			if (o->intersect(r, p0, p1) && p0 < lightDist) {
				return true;
			}
		}
	}

	return false;
}
