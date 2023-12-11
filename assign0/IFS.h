#ifndef _IFS_H_
#define _IFS_H_
#include<vector>
#include<stdio.h>
#include"matrix.h"
#include"image.h"
class IFS
{
int _nTrans;
    std::vector<Matrix> _matrices;
    std::vector<float> _probs;

    Matrix& _chooseTrans(double transChooser);

public:
    IFS() = default;

    void readFromFile(const std::string &filename);
    void renderToImage(Image &img, int nPoint, int nIteration);

};


#endif
