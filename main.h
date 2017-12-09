#ifndef MAIN_H
#define MAIN_H

#define Sample_Size 16//bit - 2^16 loudness levels
#define Sample_Rate 8000// sample/s /Hz
#define Channel_Count 2
#define Frame_Size 0.1f//0.01-0.5sec //SamplePerFrame=Sample_Rate*Frame_Size;
#define Frame_Interval 0.05f//s (1-overlap)*Frame_Size

#define XOffSet 10
#define YOffSet 10

#define XScale 2
#define YScale 0.5
#define Feature_Size 5

class Fingerprint
{
    public:
    int array[Feature_Size];
};

class FrameFeature{
public:
    Fingerprint f;
    float t;
};

#endif // MAIN_H
