//
// Created by Nycshisan on 2018/7/23.
//

#include "raytracer.h"

#include <cmath>

void RayTracer::readSceneFromFile(char *input_file) {
    _sceneParser = std::make_shared<SceneParser>(input_file);
}

void RayTracer::renderToImage(Image &img) {
    auto bgColor = _sceneParser->getBackgroundColor();
    img.SetAllPixels(bgColor);

    auto *camera = dynamic_cast<OrthographicCamera*>(_sceneParser->getCamera());
    assert(camera != nullptr);

    auto group = _sceneParser->getGroup();
    //遍历屏幕 发射光线
    for (int y = 0; y < img.Width(); ++y) {
        for (int x = 0; x < img.Height(); ++x) {
            Vec2f p(float(x) / img.Width(), float(y) / img.Height());
            auto ray = camera->generateRay(p);
            Hit hit;
            if (group->intersect(ray, hit, camera->getTMin())) {
                //有碰撞则将颜色转为最近碰撞点的颜色

                auto m = hit.getMaterial();
                auto color = m->getDiffuseColor();
                img.SetPixel(x, y, color);
            }
        }
    }
}

void RayTracer::renderDepthToImage(Image &img, float depMin, float depMax) {
    auto blackColor = Vec3f(0.f, 0.f, 0.f), whiteColor = Vec3f(1.f, 1.f, 1.f);
    img.SetAllPixels(blackColor);

    auto *camera = dynamic_cast<OrthographicCamera*>(_sceneParser->getCamera());
    assert(camera != nullptr);

    auto group = _sceneParser->getGroup();

    for (int y = 0; y < img.Width(); ++y) {
        for (int x = 0; x < img.Height(); ++x) {
            Vec2f p(float(x) / img.Width(), float(y) / img.Height());
            auto ray = camera->generateRay(p);
            Hit hit;
            if (group->intersect(ray, hit, camera->getTMin())) {
                auto t = hit.getT();
                //跟传进来的深度范围比较，若超过最大值则钳制为最大值，最小值同理
                t = std::min(depMax, t);
                t = std::max(depMin, t);
                float weight = (t - depMin) / (depMax - depMin);
                Vec3f color;
                //越远越黑，越近越白
                Vec3f::WeightedSum(color, blackColor, weight, whiteColor, 1 - weight);
                img.SetPixel(x, y, color);
            }
        }
    }
}
