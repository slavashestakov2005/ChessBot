#include <settings/recorder_stream.h>

void RecorderStream::open(std::string filename) {
    file.open(filename);
    saving_buffer = false;
    buffer.push_back("");
}

void RecorderStream::saveBuffer(bool state) {
    saving_buffer = state;
}

std::vector<std::string> const& RecorderStream::getBuffer() const {
    return buffer;
}

RecorderStream& RecorderStream::operator<<(char const& data) {
    if (saving_buffer) {
        buffer.back() += data;
    }
    file << data;
    return *this;
}

RecorderStream& RecorderStream::operator<<(std::string const& data) {
    if (saving_buffer) {
        buffer.back() += data;
    }
    file << data;
    return *this;
}

RecorderStream& RecorderStream::operator<<(int const& data) {
    return (*this) << std::to_string(data);
}

RecorderStream& RecorderStream::operator<<(PlayerType const& data) {
    if (data == PlayerType::BOT) {
        return (*this) << "bot";
    } else {
        return (*this) << "user";
    }
}

RecorderStream& RecorderStream::operator<<(std::ostream& (*manip)(std::ostream&)) {
    if (saving_buffer && manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
        buffer.push_back("");
    }
    manip(file);
    return *this;
}

RecorderStream::~RecorderStream() {
    file.close();
}
