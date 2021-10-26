#include "KDTree.h"


void KDTree::buildTree(std::vector<SceneObject*> objects) {
	//surround all objects in bounding boxes
	for (int i = 0; i < objects.size(); i++) {
		BoundingBox* box = new BoundingBox(objects.at(i));
		std::cout << *box << std::endl;
		boxList.push_back(box);
	}

	//First build root node bounding box
	//remainingObjects = objects;
	Vec3 globalMin = Vec3();
	Vec3 globalMax = Vec3();
	computeGlobalBounds(globalMin, globalMax, objects);
	root = new BoundingBox(globalMin, globalMax);
	int depth = 0;

	//find median on x-axis
	//if depth is 0, find median on x, if depth is 1, find median on y, if depth is 2, find median on z, repeat
	float median = findMedian(X_AXIS, boxList);
	
	std::vector<BoundingBox*> leftBoxes;
	std::vector<BoundingBox*> rightBoxes;

	for (int i = 0; i < boxList.size(); i++) {
		if (boxList[i]->centerVals[X_AXIS] <= median) {
			leftBoxes.push_back(boxList[i]);
		} else rightBoxes.push_back(boxList[i]);
	}

	//Then build the left and right nodes recursively

}

SceneObject* KDTree::traverseTree(Ray r, float& closestPoint) {
	return nullptr;
}

bool KDTree::findFirstIntersction(Ray r, float& lightDist) {
	return false;
}

void KDTree::computeGlobalBounds(Vec3& globalMin, Vec3& globalMax, std::vector<SceneObject*> objects) {
	//Vec3 globalMin = Vec3();
	//Vec3 unusedMax = Vec3();
	for (int i = 0; i < objects.size(); i++) {
		Vec3 localMin = Vec3();
		Vec3 localMax = Vec3();
		objects[i]->getBounds(localMin, localMax);
		if (i == 0) {
			globalMin = localMin;
			globalMax = localMax;
		}

		if (localMin.x < globalMin.x) globalMin.x = localMin.x;
		if (localMin.y < globalMin.y) globalMin.y = localMin.y;
		if (localMin.z < globalMin.z) globalMin.z = localMin.z;

		if (localMax.x > globalMax.x) globalMax.x = localMax.x;
		if (localMax.y > globalMax.y) globalMax.y = localMax.y;
		if (localMax.z > globalMax.z) globalMax.z = localMax.z;

	}
}

float KDTree::findMedian(int axis, std::vector<BoundingBox*> boxes) {
	std::vector<float> vals;
	float median;
	for (int i = 0; i < boxes.size(); i++) {
		vals.push_back(boxes[i]->centerVals[axis]);
	}
	std::sort(vals.begin(), vals.end());
	int size = vals.size();
	if (size % 2 == 0) { //even
		float v1 = vals[size / 2];
		float v2 = vals[(size - 1) / 2];
		median = (v1 + v2) / 2.0;
	} else { //odd
		median = vals[size / 2];
	}
	
	return median;
}
