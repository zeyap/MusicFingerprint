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
    CandidateDistance* dist=new CandidateDistance[candidateNum];
    for(int i=0;i<candidateNum;i++){
        int peak=FindPeak(candidates[i].tOffsetHistogram);
        int matchNum=candidates[i].matchingNum;
        dist[i].d=featureNum*featureNum/1.0f*(peak*matchNum);
        dist[i].songIndex=candidates[i].index;
    }
    candidates.clear();
    //rank dist
    SortDist(dist,candidateNum,3);

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

void Search::SortDist(CandidateDistance* dist,int len,int sortLen){
    int m=sortLen;
    if(m>len){
        m=len;
    }
    MaxHeap q(dist,m);

    CandidateDistance top=q.top();//top: max in heap

    for(int i=m;i<len;i++){
        if(dist[i].d<top.d){
            q.pop();
            q.push(dist[i]);
        }
    }

    //show min dist
    std::vector<CandidateDistance> minDist;
    for(int i=0;i<m;i++){
        CandidateDistance newd=q.pop();
        minDist.push_back(newd);
    }

}

MaxHeap::MaxHeap(CandidateDistance* newArray,int capacity){
    mCapacity=capacity;
    rearIndex=-1;
    dist=new CandidateDistance[mCapacity];
    for(int i=0;i<mCapacity;i++){
        push(newArray[i]);
    }

}

void MaxHeap::push(CandidateDistance newElem){
    rearIndex++;
    dist[rearIndex]=newElem;
    if(rearIndex){
        int currIndex=rearIndex;
        int parentIndex;
        //percolate up
        while(currIndex>0){
            parentIndex=(currIndex-1)/2;
            if(dist[currIndex].d>dist[parentIndex].d){
                CandidateDistance temp=dist[parentIndex];
                dist[parentIndex]=dist[currIndex];
                dist[currIndex]=temp;
                currIndex=parentIndex;
            }
            else{
                break;
            }
        }
    }
}

CandidateDistance MaxHeap::top(){
    return dist[0];
}

CandidateDistance MaxHeap::pop(){
    CandidateDistance* arrayAfterPop=new CandidateDistance[mCapacity];
    rearIndex--;

    for(int i=0;i<=rearIndex;i++){
        arrayAfterPop[i]=dist[i+1];
    }

    delete(dist);
    for(int i=0;i<=rearIndex;i++){
        push(arrayAfterPop[i]);
        rearIndex--;
    }
    delete(arrayAfterPop);
    return top();
}


