#include<assert.h>
#include<stdio.h>
#include<string.h>
#include"image.h"
#include"IFS.h"
#include"IFS.cpp"
#include"image.cpp"
#include"matrix.h"
#include"matrix.cpp"

int main(int argc, char *argv[]){
    char *input_file = NULL;
    int num_points = 10000;
    int num_iters = 10;
    int size = 100;
    char *output_file = NULL;
    //读命令行参数
    for (int i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-input")){
            i++;
            assert(i < argc);
            input_file = argv[i];
        }
        else if (!strcmp(argv[i], "-points")){
            i++;
            assert(i < argc);
            num_points = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-iters")){
            i++;
            assert(i < argc);
            num_iters = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-size")){
            i++;
            assert(i<argc);
            size = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-output")){
            i++;
            assert(i<argc);
            output_file=argv[i];
        }
        else {
            printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
            assert(0);
        }
    }

    //创建Image实例
    Image myimage(size, size);
    Vec3f ground_color(255.0, 255.0, 255.0);
    myimage.SetAllPixels(ground_color);

    //读IFS描述
    IFS myifs(input_file);
    myifs.read_description();

    //render the IFS to the image
    myifs.render(myimage, num_points, num_iters);

    //save the image
    myimage.SaveTGA(output_file);

    return 0;
}
