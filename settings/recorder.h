#pragma once
#include <board/move.h>
#include <settings/recorder_stream.h>

class Recorder {
public:
    Recorder();
    void settings();
    void append(Move move);
    std::vector<std::string> const& getBuffer() const;
    ~Recorder();
private:
    void write(Move move);
    void write(uint8_t cell);
    void write(Figure figure);
    std::string filename;
    RecorderStream output;
    Color prev;
    int step;
    bool default_placement;
};
