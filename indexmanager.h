#ifndef INDEXMANAGER_H
#define INDEXMANAGER_H
#include <QString>
#include <vector>
#include <QFile>
#include <QTextStream>

#define LUT_SIZE 3456
//3(20~40)*4(50~80)*4(90~120)*6(130~180)*12(190~300)

struct Frame;
struct Fingerprint;
struct Song{
    int key;
    QString name;
    std::vector<Fingerprint> pFingerprints;
    std::vector<float> fppos;
};

struct Frame{
    int songKey;
    int pos;
    Frame* next;
};

struct Fingerprint
{
    int array[5];
    Frame* pFrames;
    Frame* pRearFrame;
};//lookup table

class IndexManager
{
public:
    IndexManager();
    Fingerprint* LUT;
    static void WriteSongKeyList(QString fname);

private:

    void InitLUT();
    void GenLUT();

    std::vector<int> GetSongKeyList();
    std::vector<Song> GetSongWithKey(int i);

    int FingerprintToLUTIndex(int m,int n, int p, int q, int k);
    std::vector<int> LUTIndexToFingerprint(int i);
};

#endif // INDEXMANAGER_H
