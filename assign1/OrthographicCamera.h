#ifndef _ORTHOGRAPHICCAMERA_H
#define _ORTHOGRAPHICCAMERA_H
#include"camera.h"
class OrthographicCamera:public Camera
{
private:
    Vec3f center;
    Vec3f _direction;
    Vec3f _up;
    Vec3f _horizontal;
    int _size;
public:
    OrthographicCamera(const Vec3f& point,const Vec3f& direction,const Vec3f& up,float size);
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;

};



#endif
