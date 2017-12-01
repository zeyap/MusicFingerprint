#ifndef LINEARTRANS_H
#define LINEARTRANS_H

#include <fftw3/fftw3.h>

class lineartrans
{
public:
    lineartrans(int N);
    ~lineartrans();
    void FFT();
private:
    fftw_complex *in, *out;
    fftw_plan p;
};

#endif // LINEARTRANS_H
