#ifndef KDTREE_H
#define KDTREE_H

#include "AccelStructure.h"
#include "BoundingBox.h"

#include <algorithm>

#define AXIS 3
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class KDTree : public AccelStructure {
public:
	void buildTree(std::vector<SceneObject*> objects);
	SceneObject* traverseTree(Ray r, float& closestPoint);
	bool findFirstIntersection(Ray r, float& lightDist);

private:
	BoundingBox* root;
	std::vector<BoundingBox*> boxList;


	void computeGlobalBounds(Vec3& globalMin, Vec3& globalMax, std::vector<SceneObject*> objects);
	BoundingBox* buildTreeNode(int depth, std::vector<BoundingBox*> boxes, Vec3 min, Vec3 max);
	float findMedian(int axis, std::vector<BoundingBox*> boxes);
	SceneObject* traverseTreeNode(BoundingBox* node, Ray r, float& closestPoint);
	bool findFirstIntersectionNode(BoundingBox* node, Ray r, float& lightDist);

};





#endif
