#include "lineartrans.h"

LinearTrans::LinearTrans(std::vector<double> input, int N)
{
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    for(int i=0;i<N;i++){
        in[i][0]=input[i];
        in[i][1]=0;
    }
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    p=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);

    FFT();

    Draw(out,N);

}

LinearTrans::~LinearTrans(){
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void LinearTrans::FFT(){
    fftw_execute(p);
}
\
void LinearTrans::Draw(fftw_complex* out, int N){
    renderArea=RenderArea::getInstance();
    std::vector<QPoint> pathPoint;
    for(int i=0;i<N;i++){
        pathPoint.push_back(QPoint(i*10+50,0.001*out[i][1]+200));
    }
    renderArea->SetPathPoint(pathPoint);
}
