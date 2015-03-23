#pragma once

#include <vector>
#include <string>

#include "common.hpp"

namespace glimac {
    class Texture {
	    public:
	    	Texture(std::string name) : name(name) {
	    		loadTexture();
	    	};
	    	void loadTexture();
	    	void deleteTexture();

	    	std::string name;
	    	SDL_Surface* pTexture;
	        GLuint texture;
    };
}