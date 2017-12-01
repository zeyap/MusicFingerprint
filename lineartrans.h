#ifndef LINEARTRANS_H
#define LINEARTRANS_H

#include <fftw3/fftw3.h>
#include <vector>
#include <renderarea.h>
#include <QPoint>

class LinearTrans
{
public:
    LinearTrans(std::vector<double>input, int N);
    ~LinearTrans();
    void FFT();
private:
    fftw_complex *in, *out;
    fftw_plan p;
    RenderArea* renderArea;
    void Draw(fftw_complex* out, int N);
};

#endif // LINEARTRANS_H
