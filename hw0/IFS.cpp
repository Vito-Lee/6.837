#include "IFS.h"
#include<random>
#define N 99

void IFS::read_description()
{
    // open the file
    input = fopen(input_file, "r");
    assert(input != NULL);													//assert

    // read the number of transforms
    fscanf(input, "%d", &num_transforms);

    // < DO SOMETHING WITH num_transforms >

    // read in the transforms
    pprobability = new float[num_transforms];							//new type []
    pm = new Matrix[num_transforms];
    for (int i = 0; i < num_transforms; i++)
    {
        fscanf(input, "%f", &pprobability[i]);
        pm[i].Read3x3(input);
        // < DO SOMETHING WITH probability and m >
    }
    // close the file
    fclose(input);
}

void IFS::render(Image &image, int points, int iterations){
    int width = image.Width();
    int height = image.Height();
    for (int i = 0;i < points;i++){
        float x0 = (float)(rand() % width) / width;                                             // 不强制类型转换就是整型除法了，结果为0
        float y0 = (float)(rand() % height) / height;
        Vec2f vect(x0, y0);
        for(int k = 0;k < iterations; k++){
            float random_float = rand() % (N + 1) / (float)(N + 1);
            //有关概率的算法：假设有3个矩阵：1、三个矩阵分别掷一次骰子判断是否执行和2、掷一次骰子判断执行哪个 是不一样的：1有可能执行三个，也可能都不执行，2必执行且必仅执行一个
            float sum_probility = 0.0;
            for(int m = 0;m < num_transforms;m++){
                sum_probility += pprobability[m];
                if(random_float <= sum_probility){
                    pm[m].Transform(vect);
                    break;
                }
            }
        }
        vect.Get(x0, y0);
        x0 *= width;
        y0 *= height;
        x0 = (x0>width||x0<0) ? 0 : x0;
        y0 = (y0>height||y0<0) ? 0 : y0;
        int x1 = x0;
        int y1 = y0;
        Vec3f black_color(0.0, 0.0, 0.0);
        Vec3f green_color(0, 0, 0);                                                   //三个值都不为0的时候为什么显示不出来     改变值的大小也不会有明暗效果
        image.SetPixel(x1, y1, green_color);
    }
}
