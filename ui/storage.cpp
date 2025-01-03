#include <ui/storage.h>

std::string Storage::root;
std::unordered_map<std::string, sf::Texture> Storage::textures;
std::unordered_map<std::string, sf::Font> Storage::fonts;
std::unordered_map<std::string, sf::SoundBuffer> Storage::sounds;
std::unordered_map<std::string, sf::Music> Storage::music;

void Storage::setRoot(std::string const& newRoot) {
    root = newRoot;
}

void Storage::addTexture(std::string const& name, std::string const& path) {
    textures[name].loadFromFile(root + "/" + path);
}

void Storage::addFont(std::string const& name, std::string const& path) {
    fonts[name].loadFromFile(root + "/" + path);
}

void Storage::addSound(std::string const& name, std::string const& path) {
    sounds[name].loadFromFile(root + "/" + path);
}

void Storage::addMusic(std::string const& name, std::string const& path) {
    music[name].openFromFile(root + "/" + path);
}

sf::Texture* Storage::getTexture(std::string const& name) {
    return &textures[name];
}

sf::Font* Storage::getFont(std::string const& name) {
    return &fonts[name];
}

sf::SoundBuffer* Storage::getSound(std::string const& name) {
    return &sounds[name];
}

sf::Music* Storage::getMusic(std::string const& name) {
    return &music[name];
}
