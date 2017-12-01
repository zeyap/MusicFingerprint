#ifndef LINEARTRANS_H
#define LINEARTRANS_H

#include <fftw3/fftw3.h>
#include <vector>

class LinearTrans
{
public:
    LinearTrans(std::vector<double>input, int N);
    ~LinearTrans();
    void FFT();
private:
    fftw_complex *in, *out;
    fftw_plan p;
};

#endif // LINEARTRANS_H
