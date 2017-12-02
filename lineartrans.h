#ifndef LINEARTRANS_H
#define LINEARTRANS_H

#include <fftw3/fftw3.h>
#include <vector>
#include <renderarea.h>
#include <QPoint>
#include "main.h"

class LinearTrans
{
public:
    LinearTrans(std::vector<double> pcmInput, int fnum);
    ~LinearTrans();
    void FFT();
private:
    double *in;
    fftw_complex *out;
    fftw_plan p;
    RenderArea* renderArea;
    void ShowTag(int fnum);
    void FindFeatureVector(fftw_complex* out);
    double featurev[5][2];//freq+amp
    double basef=1/Frame_Size;//10 //Sample_Rate/(Sample_Rate*Frame_Size);
    int spf=Sample_Rate*Frame_Size;//80
};

#endif // LINEARTRANS_H
