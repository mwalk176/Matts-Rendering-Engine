#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include "../SceneObjects/SceneObject.h"


class BoundingBox {
public:
	BoundingBox(SceneObject* o);
	BoundingBox(Vec3 minVal, Vec3 maxVal);
	bool intersect(Ray& r);

	SceneObject* obj;
	bool isLeaf;

	Vec3 min;
	Vec3 max;
	Vec3 center;

	BoundingBox* left;
	BoundingBox* right;


	friend std::ostream& operator<<(std::ostream& os, BoundingBox const& b);

private:

	void computeCenter();

	
	//std::vector<BoundingBox*> children;

	Vec3 bounds[2];


};






#endif

