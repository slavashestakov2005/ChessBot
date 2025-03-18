#pragma once
#include <fstream>
#include <board/move.h>

class Recorder {
public:
    Recorder();
    void settings();
    void append(Move move);
    ~Recorder();
private:
    void write(Move move);
    void write(uint8_t cell);
    void write(Figure figure);
    std::string filename;
    std::ofstream file;
    Color prev;
    int step;
    bool default_placement;
};
