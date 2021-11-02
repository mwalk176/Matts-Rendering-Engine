#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "AccelStructure.h"
#include "BoundingBox.h"


class BruteForce : public AccelStructure {
public:
	void buildTree(std::vector<SceneObject*> objects);
	SceneObject* traverseTree(Ray r, float& closestPoint);
	bool findFirstIntersection(Ray r, float& lightDist);

private:
	std::vector<BoundingBox*> boxList;


};






#endif
