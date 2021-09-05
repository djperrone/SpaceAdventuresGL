#include "sapch.h"
#include "TextureLoader.h"
#include <spdlog/spdlog.h>

namespace SpaceAdventures {

    std::unordered_map<std::string, Novaura::Texture> TextureLoader::LoadedTextures;

    Novaura::Texture TextureLoader::LoadTexture(const std::string& path)
    {
        spdlog::trace("loadtexture1");
        if (LoadedTextures.find(path) != LoadedTextures.end())
        {
            return LoadedTextures[path];
        }
        else
        {
            LoadedTextures[path] = Novaura::Texture(path);
            return LoadedTextures[path];
        }
    }   
}