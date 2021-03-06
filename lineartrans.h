#ifndef LINEARTRANS_H
#define LINEARTRANS_H

#include <fftw3/fftw3.h>
#include <vector>
#include <renderarea.h>
#include <QPoint>
#include "main.h"
#include "search.h"

class LinearTrans
{
public:
    LinearTrans(std::vector<double> pcmInput, int fnum, int audioType);
    ~LinearTrans();
    std::vector<int> GetFeatureVector();
    std::vector<int> GetFeatureTags(int fnum);
private:
    double *in;
    fftw_complex *out;
    fftw_plan p;
    RenderArea* renderArea;
    void FFT();

    void GenFeatureVector(fftw_complex* out);
    int featurev[5][2];//freq+db
    double basef=1/Frame_Size;//10 //Sample_Rate/(Sample_Rate*Frame_Size);
    int spf=Sample_Rate*Frame_Size;//80
    int Amp2dB(double amp);
};

#endif // LINEARTRANS_H
