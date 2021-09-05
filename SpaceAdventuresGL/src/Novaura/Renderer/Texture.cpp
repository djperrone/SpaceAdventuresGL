#include "sapch.h"
#include "Texture.h"
#include <stb_image.h>
#include <glad/glad.h>

#include <spdlog/spdlog.h>

namespace Novaura {

    Texture::Texture(const std::string& path)
        : m_Width(0), m_Height(0), m_NumChannels(0)
    {
        LoadTexture(path);
        spdlog::info("tecture const");
    }

    void Texture::Bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture::UnBind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::LoadTexture(const std::string& path)
    {
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps   

        stbi_set_flip_vertically_on_load(true);
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NumChannels, 0);

        if (data)
        {
            GLenum format;
            if (m_NumChannels == 1)
                format = GL_RED;
            else if (m_NumChannels == 3)
                format = GL_RGB;
            else if (m_NumChannels == 4)
                format = GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
        else
        {
            spdlog::error("Failed to load texture");
        }
    }
}