#pragma once

#include "Novaura/Renderer/Texture.h"

namespace Novaura {

    class TextureLoader
    {
    public:
       // static Texture LoadTexture(const std::string& path);
        static Texture LoadTexture(std::string_view path);
        static void CacheTexture(std::string_view path);
        static std::unordered_map<std::string, Novaura::Texture> LoadedTextures;
    };
}