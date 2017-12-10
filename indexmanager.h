#ifndef INDEXMANAGER_H
#define INDEXMANAGER_H
#include <QString>
#include <vector>
#include <QFile>
#include <QTextStream>
#include "main.h"

#define LUT_SIZE 2305
//2(30~40)*4(50~80)*4(90~120)*6(130~180)*12(190~300)+1

class LUTHeadNode;
class LUTRecord;
class Fingerprint;

class SongInfo{
public:
    int key;
    QString name;
};

class SongData{
    public:
    std::vector<Fingerprint> fingerprints;
    std::vector<float> fppos;
};


class LUTHeadNode{
    public:
    LUTHeadNode(){
        fingerprintIndex=0;
        recordCount=0;
        pRecords=NULL;
        pRear=NULL;
    }
    int fingerprintIndex;
    int recordCount;
    LUTRecord* pRecords;
    LUTRecord* pRear;
};

class LUTRecord{//LUT
    public:
    LUTRecord(){
        next=NULL;
    }
    LUTRecord(int newSongKey,float newPos){
        songKey=newSongKey;
        pos=newPos;
        next=NULL;
    }
    int songKey;
    float pos;
    LUTRecord* next;
};


class IndexManager
{
public:
    IndexManager();
    LUTHeadNode* LUT;
    static int WriteSongKeyList(QString fname);
    static int FingerprintToLUTIndex(Fingerprint fp);
    static LUTHeadNode ReadLUT(int i);
    static std::vector<SongInfo> ReadSongKeyList();

private:

    void InitLUT();
    void GenLUT();
    void WriteLUT();

    SongData ReadSongWithKey(int i);

    static std::vector<int> LUTIndexToFingerprint(int i);
};

#endif // INDEXMANAGER_H
