#include "lineartrans.h"

LinearTrans::LinearTrans(std::vector<double> input, int N)
{
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    for(int i=0;i<N;i++){
        in[i][0]=input[i];
    }
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    p=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);

    FFT();

}

LinearTrans::~LinearTrans(){
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void LinearTrans::FFT(){
    fftw_execute(p);
}
