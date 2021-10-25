#ifndef KDTREE_H
#define KDTREE_H

#include "AccelStructure.h"
#include "BoundingBox.h"

#define AXIS 3

class KDTree : public AccelStructure {
public:
	void buildTree(std::vector<SceneObject*> objects);
	SceneObject* traverseTree(Ray r, float& closestPoint);
	bool findFirstIntersction(Ray r, float& lightDist);

private:
	BoundingBox* root;
	std::vector<BoundingBox*> boxList;


	void computeGlobalBounds(Vec3& globalMin, Vec3& globalMax, std::vector<SceneObject*> objects);
	void buildTreeNode(int depth, std::vector<SceneObject*> availableObjects);


};





#endif
