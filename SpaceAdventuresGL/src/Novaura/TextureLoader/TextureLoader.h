#pragma once

#include "Novaura/Renderer/Texture.h"

namespace Novaura {

    class TextureLoader
    {
    public:
        static Texture LoadTexture(const std::string& path);        
        static std::unordered_map<std::string, Texture> LoadedTextures;
    };
}