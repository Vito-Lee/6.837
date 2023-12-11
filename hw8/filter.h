#ifndef _FILTER_H
#define _FILTER_H
#include"vectors.h"
#include<string>
#include<memory>
#include"film.h"
class Filter
{
public:
    virtual float getWeight(float x,float y)=0;
    virtual int getSupportRadius()=0;
    static std::shared_ptr<Filter> GetDefaultFilter();
    static std::shared_ptr<Filter> GetFilterByStrategy(const string& FilterStrategy,float r);
    Vec3f getColor(int i,int j,Film *flim);

};
class BoxFilter:public Filter
{
    float _radius;
public:
    int getSupportRadius()override;
    float getWeight(float x,float y) override;
    explicit BoxFilter(float radius):_radius(radius){}
};
class TentFilter:public Filter{
    float _radius;
    public:
    int getSupportRadius()override;
    float getWeight(float x,float y)override;
    explicit TentFilter(float r):_radius(r){}
};
class GaussianFilter:public Filter
{
private:
    float _sigma;
public:
    explicit GaussianFilter(float sigma):_sigma(sigma){};
    int getSupportRadius()override;
    float getWeight(float x,float y) override;

};




#endif
