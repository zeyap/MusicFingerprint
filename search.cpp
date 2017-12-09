 #include "search.h"

Search::Search(std::vector<FrameFeature> featureBuffer)
{
    for (int i=0;i<Max_Candidate;i++){
        candidateIndexLookUpTable[i]=-1;
    }
    featureNum=featureBuffer.size();

    GenCandidates(featureBuffer);
    RankCandidates();

}

void Search::GenCandidates(std::vector<FrameFeature> featureBuffer){
    int buffersz=featureBuffer.size();
    int candidateNum=0;
    for(int i=0;i<buffersz;i++){

        int tindex=IndexManager::FingerprintToLUTIndex(featureBuffer[i].f);

        QString filename="featureOutput/LUT/"+QString::number(tindex,10)+".csv";
        QFile file(filename);
        if ( file.open(QIODevice::ReadOnly) ){
            QTextStream stream( &file );

            int lastSongIndex=-1;

            while(1){
                QString tline=stream.readLine();
                if(tline==NULL)
                    break;
                QStringList tlineList=tline.split(", ",QString::SkipEmptyParts);
                QString record1=tlineList.at(0);
                QString record2=tlineList.at(1);
                bool ok;
                int tSongIndex=record1.toInt(&ok,10);
                int tPosOnHistogram=(int) abs(record2.toFloat(&ok)-featureBuffer[i].t)/0.05f;

                if(candidateIndexLookUpTable[tSongIndex]==-1){
                    candidateIndexLookUpTable[tSongIndex]=candidateNum;

                    candidates.push_back(CandidateSong(tSongIndex));
                    candidateNum++;
                }

                if(lastSongIndex!=tSongIndex){
                    candidates[candidateIndexLookUpTable[tSongIndex]].matchingNum++;
                }

                candidates[candidateIndexLookUpTable[tSongIndex]].tOffsetHistogram[tPosOnHistogram]++;
                lastSongIndex=tSongIndex;
            }
        }

    }
}

void Search::RankCandidates(){
    //calculate dist
    int candidateNum=candidates.size();
    float* d=new float(candidateNum);
    for(int i=0;i<candidateNum;i++){
        int peak=FindPeak(candidates[i].tOffsetHistogram);
        int matchNum=candidates[i].matchingNum;
        d[i]=featureNum*featureNum/1.0f*(peak*matchNum);
    }
    candidates.clear();
    //rank dist
    RankDist(d,candidateNum);

    //show

}

int Search::FindPeak(int* tOffsetHistogram){
    int peak=0;
    for(int i=0;i<Histogram_Max_Range;i++){
        if(tOffsetHistogram[i]>peak){
            peak=tOffsetHistogram[i];
        }
    }
    return peak;
}

void Search::RankDist(float* d,int len){

}
