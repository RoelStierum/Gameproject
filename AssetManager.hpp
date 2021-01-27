#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace engine{

    /// @brief
    /// @details
    class AssetManager{
    public:
        /// @brief LoadTexture function.
        /// @details LoadTexture function for loading the texture into the memory map
        /// @param name The name for the place in the map
        /// @param fileName The place of the texture filepath. This texture will be loaded into the map
        void LoadTexture(std::string name, std::string fileName);
        /// @brief GetTexture function.
        /// @details GetTexture function for returning the texture from the memory map
        /// @param name The name for the place in the map
        sf::Texture& GetTexture(std::string name);

        /// @brief LoadFont function.
        /// @details LoadFont function for loading the font into the memory map
        /// @param name The name for the place in the map
        /// @param fileName The place of the font filepath. This font will be loaded into the map
        void LoadFont(std::string name, std::string fileName);
        /// @brief GetFont function.
        /// @details GetFont function for returning the font from the memory map
        /// @param name The name for the place in the map
        sf::Font& GetFont(std::string name);

    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _font;
    };

}
