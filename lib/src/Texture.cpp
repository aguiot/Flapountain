#include "Texture.hpp"
#include <iostream>

namespace glimac {
	void Texture::loadTexture() {
		std::string path = ("../textures/"+name);
        pTexture = IMG_Load(path.c_str());
        if (!pTexture) std::cerr << "Error loading " << path << std::endl; 
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTexture->w, pTexture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexture->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

	void Texture::deleteTexture(){
		glDeleteTextures(1, &texture);
	}
}