#ifndef _IFS_H_					//宏定义
#define _IFS_H_
#include <stdio.h>
#include "matrix.h"
#include "image.h"


class IFS
{

private:
    char *input_file = NULL;
    FILE *input = NULL;
    int num_transforms = 0;
    Matrix *pm = NULL;
    float *pprobability = NULL;

public:
    IFS(char *i)
    {
        input_file = i;
    }

    ~IFS()
    {
        delete[] pm;									//delete[]
        delete[] pprobability;
    }

    void read_description();								//函数声明和定义

    void render(Image &image, int points, int iterations);		//引用传参
};

#endif
