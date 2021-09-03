#pragma once

#include "Nova/Renderer/Texture.h"

namespace Nova {

    class TextureLoader
    {
    public:
        static Texture LoadTexture(const std::string& path);        
        static std::unordered_map<std::string, Texture> LoadedTextures;
    };
}