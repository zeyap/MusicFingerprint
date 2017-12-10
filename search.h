#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "main.h"
#include "indexmanager.h"
#define Histogram_Max_Range 12000 //MaxOffset: 12000*0.05s = 10min
#define Max_Candidate 1000

class CandidateSong{
public:
    CandidateSong(){
        index=-1;
        matchingNum=0;
        for(int i=0;i<Histogram_Max_Range;i++)
            tOffsetHistogram[i]=0;
    }
    CandidateSong(int newIndex){
        index=newIndex;
        matchingNum=0;
        for(int i=0;i<Histogram_Max_Range;i++)
            tOffsetHistogram[i]=0;
    }

    int index;
    int matchingNum;//Rm=mN/fN
    int tOffsetHistogram[Histogram_Max_Range];//=0
};

class CandidateDistance{
public:
    CandidateDistance(){}
    ~CandidateDistance(){}
    float d;
    int songIndex;
};

class MaxHeap{
public:
    MaxHeap(CandidateDistance* newArray,int capacity);

    void push(CandidateDistance newElem);
    CandidateDistance top();
    CandidateDistance pop();

    CandidateDistance* dist;
private:
    void clear(CandidateDistance* array, int capacity);
    void UpdateMaxHeap();
    int mCapacity;
    int rearIndex;
    CandidateDistance* rest;//buffer
};

class Search
{
public:
    Search(std::vector<FrameFeature> featureBuffer);
    QString RankCandidates();
private:

    void GenCandidates(std::vector<FrameFeature> featureBuffer);
    int FindPeak(int* tOffsetHistogram);
    std::vector<CandidateDistance> SortDist(CandidateDistance* dist,int len, int sortLen);
    QString FormattingResult(std::vector<CandidateDistance> res);

    int featureNum;//InRecording
    std::vector<CandidateSong> candidates;
    int candidateIndexLookUpTable[Max_Candidate];
    //index=songIndex value=indexInVector<CandidateSong>
};

#endif // SEARCH_H
