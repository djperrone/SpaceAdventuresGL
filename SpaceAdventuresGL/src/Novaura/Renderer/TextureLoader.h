#pragma once

#include "Novaura/Renderer/Texture.h"

namespace SpaceAdventures {

    class TextureLoader
    {
    public:
        static Novaura::Texture LoadTexture(const std::string& path);       
        static std::unordered_map<std::string, Novaura::Texture> LoadedTextures;
    };
}