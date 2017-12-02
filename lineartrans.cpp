#include "lineartrans.h"

LinearTrans::LinearTrans(std::vector<double> pcmInput, int fnum)
{
    int N=pcmInput.size();
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    for(int i=0;i<N;i++){
        in[i][0]=pcmInput[i];
        in[i][1]=0;
    }
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    p=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);

    FFT();

    FindFeatureVector(out);

    Draw(out,N,fnum);

}

LinearTrans::~LinearTrans(){
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void LinearTrans::FFT(){
    fftw_execute(p);
}

void LinearTrans::FindFeatureVector(fftw_complex* out){
    double tempf;
    int bandIdx;
    for(int i=0;i<5;i++){
        featurev[i]=0;
    }
    for(int i=0;i<spf;i++){
        bandIdx=-1;
        tempf=basef*i;
        if(tempf>30&&tempf<=40){
            bandIdx=0;
        }else if(tempf>40&&tempf<=80){
            bandIdx=1;
        }else if(tempf>80&&tempf<=120){
            bandIdx=2;
        }else if(tempf>120&&tempf<=180){
            bandIdx=3;
        }else if(tempf>180&&tempf<=300){
            bandIdx=4;
        }
        if(bandIdx!=-1){
            if(std::abs(out[i][0])>featurev[bandIdx]){
                featurev[bandIdx]=tempf;
            }
        }
    }
}
\
void LinearTrans::Draw(fftw_complex* out, int N, int fnum){
    renderArea=RenderArea::getInstance();
    std::vector<QPoint> pathPoint;
    for(int i=0;i<N;i++){
        pathPoint.push_back(QPoint(i*XScale+XOffSet+XOffSet*1*fnum,YScale*out[i][0]+YOffSet));
    }
    renderArea->SetPathPoint(pathPoint);
}
