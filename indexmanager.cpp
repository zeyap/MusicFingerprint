#include "indexmanager.h"

IndexManager::IndexManager()
{
    InitLUT();
}

void IndexManager::InitLUT(){
    LUT=new Fingerprint[LUT_SIZE];
    for (int i=0;i<LUT_SIZE;i++){
        LUT[i].index=i;
        std::vector<int> newArray=LUTIndexToFingerprint(i);
        for(int j=0;j<5;j++){
            LUT[i].array[j]=newArray[j];
        }
        LUT[i].pFrames=NULL;
        LUT[i].pRearFrame=NULL;
    }
    GenLUT();
}

void IndexManager::GenLUT(){
    std::vector<int> songKeys=GetSongKeyList();
    for(int i=0;i<songKeys.size();i++){

        Song* newSong=GetSongWithKey(songKeys[i]);
        int fpNum=newSong->pFingerprints.size();
        for (int j=0;j<fpNum;j++){

            Frame newFrame;
            newFrame.songKey=songKeys[i];

            newFrame.pos=newSong->fppos[j];
            newFrame.next=NULL;

            int m,n,p,q,k;
            m=newSong->pFingerprints[j].array[0];
            n=newSong->pFingerprints[j].array[1];
            p=newSong->pFingerprints[j].array[2];
            q=newSong->pFingerprints[j].array[3];
            k=newSong->pFingerprints[j].array[4];
            int LUTindex=FingerprintToLUTIndex(m,n,p,q,k);

            if(LUT[LUTindex].pFrames==NULL){
                LUT[LUTindex].pFrames=newFrame;
                LUT[LUTindex].pRearFrame=LUT[LUTindex].pFrames;
            }else{
                LUT[LUTindex].pRearFrame->next=newFrame;
            }

        }
    }
    //Sort songs in a bucket
    //Write to file
}

std::vector<int> IndexManager::GetSongKeyList(){

}

std::vector<Song> IndexManager::GetSongWithKey(int i){

}

int IndexManager::FingerprintToLUTIndex(int m,int n, int p, int q, int k){
    int i[5];
    i[0]=(m-20)/10;//最高位
    i[1]=(n-50)/10;
    i[2]=(p-90)/10;
    i[3]=(q-130)/10;
    i[4]=(k-190)/10;//最低位

    return (((i[0]*4+i[1])*4+i[2])*6+i[3])*12+i[4];
}

std::vector<int> IndexManager::LUTIndexToFingerprint(int i){
    std::vector<int> fp;
    int m,n,p,q,k;//3 4 4 6 12
    m=(i/(4*4*6*12))%3*10+20;
    n=(i/(4*6*12))%4*10+50;
    p=(i/(6*12))%4*10+90;
    q=(i/12)%6*10+130;
    k=i%12*10+190;
    fp.push_back(k);
    fp.push_back(q);
    fp.push_back(p);
    fp.push_back(n);
    fp.push_back(m);
    return fp;
}

void IndexManager:: WriteSongKeyList(QString fname){
    int fileIndex=GenFileIndex(fname);
    QString filename="featureOutput/SongKeyList"+QString::number(fileIndex,10)+".csv";
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        //check repetition
        QTextStream stream( &file );
        stream << songIndex<<", ";
        stream <<fname<<", ";
        stream<<"\n";

    }
}

int IndexManager::GenFileIndex(QString fname){
    int newFileIndex;
    QStringList list=fname.split("",QString::SkipEmptyParts);
    return newFileIndex;
}
