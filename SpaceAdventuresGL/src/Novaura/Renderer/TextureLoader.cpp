#include "sapch.h"
#include "TextureLoader.h"
#include <spdlog/spdlog.h>

namespace Novaura {

    std::unordered_map<std::string, Novaura::Texture> TextureLoader::LoadedTextures;

   /* Novaura::Texture TextureLoader::LoadTexture(const std::string& path)
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
    }*/

    Texture TextureLoader::LoadTexture(std::string_view path)
    {
        spdlog::trace("loadtexture1");
        if (LoadedTextures.find(path.data()) != LoadedTextures.end())
        {
            return LoadedTextures[path.data()];
        }
        else
        {
            LoadedTextures[path.data()] = Texture(path);
            return LoadedTextures[path.data()];
        }
    }

    void TextureLoader::CacheTexture(std::string_view path)
    {
        if (LoadedTextures.find(path.data()) == LoadedTextures.end())
        {
            LoadedTextures[path.data()] = Novaura::Texture(path);
        }
       
    }
}