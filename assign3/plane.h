#ifndef _PLANE_H
#define _PLANE_H
#include"object3d.h"
#include "object3d.h"
#include "material.h"

class Plane : public Object3D {
    Vec3f _normal;
    float _offset;

public:
    Plane(const Vec3f &normal, float offset, Material *m);
    Plane(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, Material *m);

    bool intersect(const Ray &r, Hit &h, float tmin) override;
};
#endif
