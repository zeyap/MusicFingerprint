#include "indexmanager.h"

IndexManager::IndexManager()
{
    InitLUT();
    GenLUT();
}

void IndexManager::InitLUT(){

    LUT=new LUTHeadNode[LUT_SIZE];

}

void IndexManager::GenLUT(){
    std::vector<SongInfo> songsInfo=ReadSongKeyList();
    for(int i=0;i<songsInfo.size();i++){

        SongData newSongData=ReadSongWithKey(songsInfo[i].key);
        int fpNum=newSongData.fingerprints.size();
        for (int j=0;j<fpNum;j++){
            LUTRecord* newRecord=new LUTRecord;
            newRecord->songKey=songsInfo[i].key;
            newRecord->pos=newSongData.fppos[j];

            int LUTindex=FingerprintToLUTIndex(newSongData.fingerprints[j]);

            if(LUT[LUTindex].recordCount==0){
                LUT[LUTindex].pRecords=newRecord;
                LUT[LUTindex].pRear=LUT[LUTindex].pRecords;
            }else{
                LUT[LUTindex].pRear->next=newRecord;
                LUT[LUTindex].pRear=LUT[LUTindex].pRear->next;
            }
            LUT[LUTindex].recordCount++;
        }
    }

    //Sort songs in a bucket
    WriteLUT();
}

void IndexManager::WriteLUT(){
    for(int i=0;i<LUT_SIZE;i++){
        if(LUT[i].recordCount!=0){
            QString filename="featureOutput/LUT/"+QString::number(i,10)+".csv";
            QFile file(filename);
            if ( file.open(QIODevice::WriteOnly) )
            {
                QTextStream stream( &file );
                LUTRecord* pRecord;
                pRecord=LUT[i].pRecords;
                while(pRecord!=NULL){
                    stream << pRecord->songKey<<", ";
                    stream <<pRecord->pos<<"\n";
                    pRecord=pRecord->next;
                }
            }
            file.close();
        }
    }
}


int IndexManager:: WriteSongKeyList(QString fname){
    QString filename="featureOutput/SongKeyList.csv";
    QFile file(filename);
    int songIndex=0;
    if ( file.open(QIODevice::ReadWrite) )
    {
        //check repetition
        QTextStream stream( &file );
        while(1){
            QString tline=stream.readLine();
            if(tline==NULL)
                break;
            QStringList tlineList=tline.split(", ",QString::SkipEmptyParts);
            QString record1=tlineList.at(0);
            QString tname=tlineList.at(1);
            bool ok;
            int tindex=record1.toInt(&ok, 10);
            if(songIndex==tindex){
                if(tname==fname){
                    return -1;//already exist
                    break;
                }
                songIndex++;
            }else{
                break;
            }
        }

        stream << songIndex<<", ";
        stream <<fname<<", ";
        stream<<"\n";
    }
    file.close();
    return songIndex;
}

std::vector<SongInfo> IndexManager::ReadSongKeyList(){
    std::vector<SongInfo> songsInfo;
    QString filename="featureOutput/SongKeyList.csv";
    QFile file(filename);
    if ( file.open(QIODevice::ReadOnly) )
    {
        QTextStream stream( &file );
        while(1){
            QString tline=stream.readLine();
            if(tline==NULL)
                break;
            QStringList tlineList=tline.split(",",QString::SkipEmptyParts);
            QString record1=tlineList.at(0);
            bool ok;
            int tindex=record1.toInt(&ok, 10);
            QString songName=tlineList.at(1);
            SongInfo newSongInfo;
            newSongInfo.key=tindex;
            newSongInfo.name=songName;
            songsInfo.push_back(newSongInfo);
        }
    }
    file.close();
    return songsInfo;
}

SongData IndexManager::ReadSongWithKey(int i){
    SongData newSongData;
    QString filename="featureOutput/bySong/"+QString::number(i,10)+".csv";
    QFile file(filename);
    if ( file.open(QIODevice::ReadOnly) ){
        QTextStream stream( &file );
        stream.readLine();//skip head line
        while(1){
            QString tline=stream.readLine();
            if(tline==NULL)
                break;
            QStringList tlineList=tline.split(",",QString::SkipEmptyParts);
            QString record[6];
            Fingerprint newFp;
            for(int j=0;j<5;j++){
                record[j]=tlineList.at(j);
                bool ok;
                int tindex=record[j].toInt(&ok,10);
                newFp.array[j]=tindex;
            }
            record[5]=tlineList.at(5);
            float tpos=record[5].toFloat();
            newSongData.fingerprints.push_back(newFp);
            newSongData.fppos.push_back(tpos);
        }
    }
    file.close();
    return newSongData;
}

int IndexManager::FingerprintToLUTIndex(Fingerprint fp){
    int i[Feature_Size];

    const int bandLowerBounds[5]={30,50,90,130,190};
    const int offsets[5]={3,5,5,7,13};

    for(int j=0;j<Feature_Size;j++){
        if(fp.array[j]==0){
            i[j]=offsets[j]-1;
        }else{
            i[j]=(fp.array[j]-bandLowerBounds[j])/10;
        }
    }

    int res=(((i[0]*offsets[1]+i[1])*offsets[2]+i[2])*offsets[3]+i[3])*offsets[4]+i[4];
    if(res<0){
        return -1;
    }

    return res;
}

std::vector<int> IndexManager::LUTIndexToFingerprint(int i){
    std::vector<int> fp;
    int m,n,p,q,k;
    m=(i/(5*5*7*13))%3*10+20;
    n=(i/(5*7*13))%4*10+50;
    p=(i/(7*13))%4*10+90;
    q=(i/13)%6*10+130;
    k=i%13*10+190;
    fp.push_back(k);
    fp.push_back(q);
    fp.push_back(p);
    fp.push_back(n);
    fp.push_back(m);
    return fp;
}
