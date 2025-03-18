#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <settings/settings.h>

class RecorderStream {
public:
    void open(std::string filename);
    void saveBuffer(bool state);
    std::vector<std::string> const& getBuffer() const;
    RecorderStream& operator<<(char const& data);
    RecorderStream& operator<<(std::string const& data);
    RecorderStream& operator<<(int const& data);
    RecorderStream& operator<<(PlayerType const& data);
    RecorderStream& operator<<(std::ostream& (*manip)(std::ostream&));
    ~RecorderStream();
private:
    bool saving_buffer;
    std::ofstream file;
    std::vector<std::string> buffer;
};
