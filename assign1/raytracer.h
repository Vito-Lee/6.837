#ifndef _RAYTRACER_H
#define _RAYTRACER_H
#include"image.h"
#include<memory>
#include"scene_parser.h"
#include"hit.h"
#include"ray.h"
#include"OrthographicCamera.h"
#include"group.h"
#include"material.h"
class raytracer
{
private:
    /* data */
    std::shared_ptr<SceneParser> _sceneparser;
public:
    void ReadFromFile(char* input_file);
    void renderToImage(Image& image);
    void renderDepthToImage(Image& image,float depMin,float depMax);
};



#endif
