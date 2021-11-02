#include "BoundingBox.h"

BoundingBox::BoundingBox(SceneObject* o) {
    obj = o;
    isLeaf = true;
    min = Vec3();
    max = Vec3();
    center = Vec3();
    o->getBounds(min, max);
    bounds[0] = min;
    bounds[1] = max;
    left = nullptr;
    right = nullptr;
    computeCenter();
}

BoundingBox::BoundingBox(Vec3 minVal, Vec3 maxVal) {
    obj = nullptr;
    isLeaf = false;
    min = minVal - 1.0;
    max = maxVal + 1.0;
    center = Vec3();
    bounds[0] = min;
    bounds[1] = max;
    left = nullptr;
    right = nullptr;
    computeCenter();
}

bool BoundingBox::intersect(Ray& r) {

    //largely inspired and taken from ScratchaPixel's method on ray box intersections
    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
    float tx0, tx1, ty0, ty1, tz0, tz1;

    tx0 = (bounds[r.sign[0]].x - r.o.x) * r.inv.x;
    tx1 = (bounds[1 - r.sign[0]].x - r.o.x) * r.inv.x;
    ty0 = (bounds[r.sign[1]].y - r.o.y) * r.inv.y;
    ty1 = (bounds[1 - r.sign[1]].y - r.o.y) * r.inv.y;

    if (tx0 > ty1 || ty0 > tx1) return false;
    if (ty0 > tx0) tx0 = ty0;
    if (ty1 < tx1) tx1 = ty1;

    tz0 = (bounds[r.sign[2]].z - r.o.z) * r.inv.z;
    tz1 = (bounds[1 - r.sign[2]].z - r.o.z) * r.inv.z;

    if (tx0 > tz1 || tz0 > tx1) return false;
    if (tz0 > tx0) tx0 = tz0;
    if (tz1 < tx1) tx1 = tz1;

    return true;
}

void BoundingBox::computeCenter() {
    float xMidpoint = (min.x + max.x) / 2.0;
    float yMidpoint = (min.y + max.y) / 2.0;
    float zMidpoint = (min.z + max.z) / 2.0;
    center = Vec3(xMidpoint, yMidpoint, zMidpoint);
    centerVals[0] = center.x;
    centerVals[1] = center.y;
    centerVals[2] = center.z;
}

std::ostream& operator<<(std::ostream& os, BoundingBox const& b) {
    if (b.left == nullptr && b.right == nullptr) {
        os << "Bounding Box:\n\tMin: " << b.min << "\n\tMax: " << b.max << "\n\tCenter: " << b.center << 
            "\n\tObject: " << b.obj->toString() << "\n";
    } else if (b.left == nullptr) {
        os << "Bounding Box:\n\tMin: " << b.min << "\n\tMax: " << b.max << "\n\tCenter: " << b.center <<
            "\n\tLeft: NULL"  << "\n\tRight: " << *b.right << "\n\n";
    } else if (b.right == nullptr) {
        os << "Bounding Box:\n\tMin: " << b.min << "\n\tMax: " << b.max << "\n\tCenter: " << b.center <<
            "\n\tLeft: " << *b.left << "\n\tRight: NULL" << "\n\n";
    } else {
        os << "Bounding Box:\n\tMin: " << b.min << "\n\tMax: " << b.max << "\n\tCenter: " << b.center <<
            "\n\tLeft: " << *b.left << "\n\tRight: " << *b.right << "\n\n";
    }
   
    return os;
}
