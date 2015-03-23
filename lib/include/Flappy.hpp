#pragma once

#include <vector>

#include "common.hpp"
#include "Texture.hpp"
#include "Pipe.hpp"

namespace glimac {

class Flappy {
    void build();

    public:
        Flappy() : position(glm::vec3(0.f,-5.f,0.f)) {
            build();
        }

        const ShapeVertex* getDataPointer() const {
            return &m_vertices[0];
        }
        
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

        void launch(std::vector<Pipe> &pipes);
        void applyGravity(Force3D force);
        void update(float dt, std::vector<Pipe> &pipes);
        void load(VAO &vao, VBO &vbo);
        void display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light light);

    private:
        glm::vec3 position;
        glm::vec3 velocity;
        float mass;
        glm::vec3 force;
        int originIndex;
        int destinationIndex;

        std::vector<ShapeVertex> m_vertices;        
        GLsizei m_nVertexCount;
    };
    
}