#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#define _USE_MATH_DEFINES

#include "../../Utils/Vec3.h"
#include "../../Utils/Ray.h"
#include "../../Materials/Material.h"
#include "../../Materials/MDebugMat.h"
#include <vector>

class SceneObject {
public:
	SceneObject();
	Vec3 getPos();
	virtual bool intersect(Ray r, float& p0, float& p1) = 0;
	virtual Vec3 computeNormal(Vec3 intersectionPoint) = 0;
	virtual Vec3 getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, float& angleToObject, Vec3 intersectionPoint) = 0;
	void getBounds(Vec3& minimum, Vec3& maximum);
	Material* getMaterial(int mType);
	void setPrimaryMaterial(Material* m);

	std::vector<Material*> getMaterials();

	virtual std::string toString() = 0;
	//virtual friend std::ostream& operator<<(std::ostream& os, SceneObject const& s) = 0;

	int shapeType = -1; //-1 no type set yet, 0 sphere, 1 triangle, 2 rectangle

protected:
	Vec3 pos;
	std::vector<Material*> materials;
	Material* primaryMaterial;
	Vec3 min;
	Vec3 max;

	virtual void computeBounds() = 0;

private:

};



#endif