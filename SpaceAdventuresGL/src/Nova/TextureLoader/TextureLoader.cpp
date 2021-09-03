#include "sapch.h"
#include "TextureLoader.h"
#include <spdlog/spdlog.h>

namespace Nova {

    std::unordered_map<std::string, Texture> TextureLoader::LoadedTextures;

    Texture TextureLoader::LoadTexture(const std::string& path)
    {
        spdlog::trace("loadtexture1");
        if (LoadedTextures.find(path) != LoadedTextures.end())
        {
            return LoadedTextures[path];
        }
        else
        {
            LoadedTextures[path] = Texture(path);
            return LoadedTextures[path];
        }
    }    
}