#ifndef _GROUP_H
#define _GROUP_H
#include"object3d.h"
#include<vector>
class Group:public Object3D
{
private:
    int _nobjects;
    vector<Object3D*> objs;
public:
    explicit Group(int n);
    void addObject(int index,Object3D* obj);
    virtual bool intersect(const Ray &r,Hit &h,float tmin);
};


#endif
