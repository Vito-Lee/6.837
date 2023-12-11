#ifndef _SPHERE_H
#define _SPHERE_H
#include"object3d.h"
class Sphere:public Object3D
{
private:
    Vec3f _center;
    float _radius;
public:
    Sphere(Vec3f point,float r,Material* material){
        _center=point;
        _radius=r;
        _material=material;
    }
    virtual bool intersect(const Ray&r,Hit &h,float tmin);




};




#endif
