#include "lineartrans.h"
#include "mainwindowmf.h"

LinearTrans::LinearTrans(std::vector<double> pcmInput, int fnum, int audioType)
{
    int N=pcmInput.size();
    in = (double*)fftw_malloc(sizeof(double)*N);
    for(int i=0;i<N;i++){
        in[i]=pcmInput[i];
    }
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
    p=fftw_plan_dft_r2c_1d(N,in,out,FFTW_ESTIMATE);

    FFT();

    GenFeatureVector(out);

}

LinearTrans::~LinearTrans(){
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void LinearTrans::FFT(){
    fftw_execute(p);
}

void LinearTrans::GenFeatureVector(fftw_complex* out){
    double tempf;
    int bandIdx;
    for(int i=0;i<5;i++){
        featurev[i][0]=0;//freq
        featurev[i][1]=0;//amp
    }
    for(int i=0;i<spf/2;i++){
        bandIdx=-1;
        tempf=basef*i;
        if(tempf>=30&&tempf<=40){
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
            double amp=std::sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
            int db=Amp2dB(amp);
            if(db>featurev[bandIdx][1]){
                featurev[bandIdx][0]=(int)tempf;
                featurev[bandIdx][1]=db;
            }
        }
    }
}

std::vector<int> LinearTrans::GetFeatureVector(){
    std::vector<int> v;
    for(int i=0;i<5;i++){
        v.push_back(featurev[i][0]);
    }
    return v;
}

std::vector<int> LinearTrans::GetFeatureTags(int fnum){

    std::vector<int> newTag;
    newTag.push_back(0);
    newTag.push_back(fnum);
    for(int i=0;i<5;i++){
        newTag.push_back(featurev[i][0]);
        newTag.push_back(featurev[i][1]);
    }
    return newTag;
}

int LinearTrans::Amp2dB(double amp){
//pcm stores amplitude/voltage
    int dB=(int)20*log10(std::abs(amp));
    return dB;
}
