#include "sapch.h"
#include "TextureLoader.h"
#include <spdlog/spdlog.h>

namespace SpaceAdventures {

    std::unordered_map<std::string, Nova::Texture> TextureLoader::LoadedTextures;

    Nova::Texture TextureLoader::LoadTexture(const std::string& path)
    {
        spdlog::trace("loadtexture1");
        if (LoadedTextures.find(path) != LoadedTextures.end())
        {
            return LoadedTextures[path];
        }
        else
        {
            LoadedTextures[path] = Nova::Texture(path);
            return LoadedTextures[path];
        }
    }   
}