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
		if (boxList[i]->centerVals[X_AXIS] < median) {
			leftBoxes.push_back(boxList[i]);
		} else if (boxList[i]->centerVals[X_AXIS] == median) { //randomly assign to left or right
			float threshold = 0.5;
			if ((float)rand() / RAND_MAX <= threshold) leftBoxes.push_back(boxList[i]);
			else rightBoxes.push_back(boxList[i]);
		} else {
			rightBoxes.push_back(boxList[i]);
		}
	}

	//Then build the left and right nodes recursively
	Vec3 leftMax = Vec3(median, globalMax.y, globalMax.z);
	Vec3 rightMin = Vec3(median, globalMin.y, globalMin.z);
	root->left = buildTreeNode(depth++, leftBoxes, globalMin, leftMax);
	root->right = buildTreeNode(depth++, rightBoxes, rightMin, globalMax);

	std::cout << "KD-Tree Built\n";
	std::cout << "Root: \n" << *root << "\n\n";
}

SceneObject* KDTree::traverseTree(Ray r, float& closestPoint) {
	//start at root node
	if (root->intersect(r)) {
		float pLeft = INFINITY;
		SceneObject* leftObj = traverseTreeNode(root->left, r, pLeft);

		float pRight = INFINITY;
		SceneObject* rightObj = traverseTreeNode(root->right, r, pRight);


		if (leftObj != nullptr && rightObj != nullptr) {
			//we want to first return objects in front of us
			//as opposed to the object we may or may not be inside of
			//if (pLeft < pRight && pLeft >= 0) {
			//	closestPoint = pLeft;
			//	return leftObj;
			//}
			//else if (pRight < pLeft && pRight >= 0) {
			//	closestPoint = pRight;
			//	return rightObj;
			//}

			if (pLeft < pRight) {
				closestPoint = pLeft;
				return leftObj;
			}
			else {
				closestPoint = pRight;
				return rightObj;
			}
		}
		else if (leftObj != nullptr) {
			closestPoint = pLeft;
			return leftObj;
		}
		else if (rightObj != nullptr) {
			closestPoint = pRight;
			return rightObj;
		}
		else return nullptr;
	}

	return nullptr;
}

bool KDTree::findFirstIntersection(Ray r, float& lightDist) {
	if (root->intersect(r)) {
		if (findFirstIntersectionNode(root->left, r, lightDist)) return true;
		else if (findFirstIntersectionNode(root->right, r, lightDist)) return true;
		else return false;
	}
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

BoundingBox* KDTree::buildTreeNode(int depth, std::vector<BoundingBox*> boxes, Vec3 min, Vec3 max) {
	if (boxes.size() == 0) return nullptr;
	if (boxes.size() == 1) return boxes[0];
	int axis = depth % AXIS;
	if (boxes.size() == 2) {
		BoundingBox* node = new BoundingBox(min, max);
		node->left = boxes[0];
		node->right = boxes[1];
		return node;
	}

	BoundingBox* node = new BoundingBox(min, max);
	//int axis = depth % AXIS;
	float median = findMedian(axis, boxes);

	std::vector<BoundingBox*> leftBoxes;
	std::vector<BoundingBox*> rightBoxes;

	for (int i = 0; i < boxes.size(); i++) {
		if (boxes[i]->centerVals[axis] <= median) {
			leftBoxes.push_back(boxes[i]);
		} else if (boxes[i]->centerVals[axis] == median) { //randomly assign to left or right
			//float threshold = 0.5;
			//if ((float)rand() / RAND_MAX <= threshold) leftBoxes.push_back(boxList[i]);
			//else rightBoxes.push_back(boxList[i]);
		} else {
			rightBoxes.push_back(boxList[i]);
		}
	}

	//Then build the left and right nodes recursively
	Vec3 leftMax;
	Vec3 rightMin;
	switch (axis) {
	case X_AXIS:
		leftMax = Vec3(median, max.y, max.z);
		rightMin = Vec3(median, min.y, min.z);
	case Y_AXIS:
		leftMax = Vec3(max.x, median, max.z);
		rightMin = Vec3(min.z, median, min.z);
	case Z_AXIS:
		leftMax = Vec3(max.x, max.y, median);
		rightMin = Vec3(min.x, min.y, median);
	}

	node->left = buildTreeNode(depth++, leftBoxes, min, leftMax);
	node->right = buildTreeNode(depth++, rightBoxes, rightMin, max);

	return node;

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

SceneObject* KDTree::traverseTreeNode(BoundingBox* node, Ray r, float& closestPoint) {
	if (node == nullptr) return nullptr;
	if (node->isLeaf) { //don't worry about intersecting the bounding box
		float p0 = INFINITY;
		float p1 = INFINITY;
		if (node->obj->intersect(r, p0, p1)) {
			closestPoint = p0;
			return node->obj;
		}
	}
	if (node->intersect(r)) {
		float pLeft = INFINITY;
		SceneObject* leftObj = traverseTreeNode(node->left, r, pLeft);

		float pRight = INFINITY;
		SceneObject* rightObj = traverseTreeNode(node->right, r, pRight);
				
		if (leftObj != nullptr && rightObj != nullptr) {
			//we want to first return objects in front of us
			//	if (pLeft < pRight && pLeft >= 0) {
			//		closestPoint = pLeft;
			//		return leftObj;
			//	} else if (pRight < pLeft && pRight >= 0) {
			//		closestPoint = pRight;
			//		return rightObj;
			//	}
			if (pLeft < pRight) {
				closestPoint = pLeft;
				return leftObj;
			} else {
				closestPoint = pRight;
				return rightObj;
			}
		} else if (leftObj != nullptr) {
			closestPoint = pLeft;
			return leftObj;
		} else if (rightObj != nullptr) {
			closestPoint = pRight;
			return rightObj;
		} else return nullptr;
	}

	return nullptr;
}

bool KDTree::findFirstIntersectionNode(BoundingBox* node, Ray r, float& lightDist) {
	if (node == nullptr) return false;
	if (node->isLeaf) {
		float p0 = INFINITY;
		float p1 = INFINITY;
		if (node->obj->intersect(r, p0, p1)) {
			if (p0 < lightDist) return true;
			else return false;
		}
	}
	if (node->intersect(r)) {
		if (findFirstIntersectionNode(node->left, r, lightDist)) return true;
		else if (findFirstIntersectionNode(node->right, r, lightDist)) return true;
		else return false;
	}


	return false;

}