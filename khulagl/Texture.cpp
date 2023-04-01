//
//  Texture.cpp
//  khulagl
//
//  Created by Anirudh on 01/04/23.
//

#include "Texture.hpp"

Texture::Texture(const std::string& filepath)
    : id(0), filepath(filepath), localBuffer(nullptr), width(0), height(0), bpp(0)
{
    load();
}

Texture::~Texture()
{
    unload();
}
void Texture::load() {
    stbi_set_flip_vertically_on_load(true);
    localBuffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

    if (!localBuffer)
    {
        fprintf(stderr, "Failed to load texture\n");
        exit(1);
    }
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (localBuffer) {
        stbi_image_free(localBuffer);
    }
}

void Texture::unload()
{
    glDeleteTextures(1, &id);
    id = 0;
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
