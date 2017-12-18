# MusicFingerprint

<h3>Recorder</h3>

Read audio input from Microphone. [QMultimedia library](http://doc.qt.io/qt-5/qtmultimedia-index.html)

<h3>Preprocessing</h3>

Format input recordings. [QMultimedia library](http://doc.qt.io/qt-5/qtmultimedia-index.html)

Frame the recordings into overlapping audio fragments

<h3>Linear Transformation</h3>

Do Fast Fourier Transform on each frame of recording. [FFTW3 library](http://fftw.org/)

Generate a feature vector/**Music fingerprint** for each frame. [Shazam](https://dl.acm.org/citation.cfm?doid=1145287.1145312)'s method. Originally implemented

For each song, write feature vectors into a file

![](zeyap.github.io/assets/images/mf_1.png)

<h3>Index Manager</h3>

Index feature vectors. [Hatisma & Kalker](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.16.2893). Originally implemented

Generate Reverse hash lookup-tables from (fixed number of) features to songs

<h3>Search</h3>

Find possible music candidates -- match features from a new recording with existing music through Lookup Table. Originally implemented

Sort candidates by Distance to the recording in a Priority Queue/Maximum Heap

![](zeyap.github.io/assets/images/mf_2.png)
