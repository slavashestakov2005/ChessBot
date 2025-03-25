#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Storage {
public:
    static void setRoot(std::string const& newRoot);

    static void addTexture(std::string const& name, std::string const& path);
    static void addFont(std::string const& name, std::string const& path);
    static void addSound(std::string const& name, std::string const& path);
    static void addMusic(std::string const& name, std::string const& path);

    static sf::Texture* getTexture(std::string const& name);
    static sf::Font* getFont(std::string const& name);
    static sf::SoundBuffer* getSound(std::string const& name);
    static sf::Music* getMusic(std::string const& name);
private:
    static std::string root;
    static std::unordered_map<std::string, sf::Texture> textures;
    static std::unordered_map<std::string, sf::Font> fonts;
    static std::unordered_map<std::string, sf::SoundBuffer> sounds;
    static std::unordered_map<std::string, sf::Music> music;
};
