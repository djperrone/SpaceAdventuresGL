#pragma once

#include "Nova/Renderer/Texture.h"

namespace SpaceAdventures {

    class TextureLoader
    {
    public:
        static Nova::Texture LoadTexture(const std::string& path);       
        static std::unordered_map<std::string, Nova::Texture> LoadedTextures;
    };
}