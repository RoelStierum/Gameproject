#include "AssetManager.hpp"

namespace engine{

    //LoadTexture function for loading the texture into the memory map
    void AssetManager::LoadTexture(std::string name, std::string fileName) {
        sf::Texture tex;

        if(tex.loadFromFile(fileName)){
            _textures[name] = tex;
        }
    }

    //GetTexture function for returning the texture from the memory map
    sf::Texture& AssetManager::GetTexture(std::string name) {
        return _textures.at(name);
    }

    //LoadFont function for loading the font into the memory map
    void AssetManager::LoadFont(std::string name, std::string fileName) {
        sf::Font font;

        if(font.loadFromFile(fileName)){
            _font[name] = font;
        }
    }

    //GetFont function for returning the font from the memory map
    sf::Font& AssetManager::GetFont(std::string name) {
        return _font.at(name);
    }

}