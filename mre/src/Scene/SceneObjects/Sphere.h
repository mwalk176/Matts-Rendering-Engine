#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.h"

class Sphere : public SceneObject {
public:
	Vec3 getPos();
	bool intersect(Ray r, double& p0, double& p1);

	std::string toString();
	//friend std::ostream& operator<<(std::ostream& os, SceneObject const& s);


private:
	Vec3 pos;
	double radius;

};

#endif