#include "lineartrans.h"

lineartrans::lineartrans(int N)
{
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    p=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);

}

lineartrans::~lineartrans(){
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void lineartrans::FFT(){
    fftw_execute(p);
}
