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
	virtual bool intersect(Ray r, double& p0, double& p1) = 0;
	virtual Vec3 computeNormal(Vec3 intersectionPoint) = 0;
	virtual Vec3 getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, double& angleToObject, Vec3 intersectionPoint) = 0;
	Material* getMaterial(std::string mType);
	void setPrimaryMaterial(Material* m);

	std::vector<Material*> getMaterials();

	virtual std::string toString() = 0;
	//virtual friend std::ostream& operator<<(std::ostream& os, SceneObject const& s) = 0;

protected:
	Vec3 pos;
	std::vector<Material*> materials;
	Material* primaryMaterial;

private:

};



#endif