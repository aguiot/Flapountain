#pragma once

#include <vector>
#include <string>

#include "Texture.hpp"
#include "Sphere.hpp"
#include "VBO.hpp"
#include "VAO.hpp"

#include <common.hpp>

namespace glimac {

    class Skybox {

        Sphere shape;

        public:
            void load(VAO &vao, VBO &vbo);
            Skybox(Sphere shape) : shape(shape) {}
            void display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uint32 tStart, Uniforms &uniforms, Light &light);
    };
    
}