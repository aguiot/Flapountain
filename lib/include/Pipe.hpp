#pragma once

#include <vector>

#include "common.hpp"
#include "Texture.hpp"

namespace glimac {

class Pipe {
    void build(float radius);

    public:
        Pipe(float radius, glm::vec3 position) : position(position) {
            build(radius);
        }

        const ShapeVertex* getDataPointer() const {
            return &m_vertices[0];
        }
        
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

        glm::vec3 getPosition() {
            return position + glm::vec3(0.f,height,0.f);
        }

        float getHeight() {
            return height;
        }

        void load(VAO &vao, VBO &vbo);
        void display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light light);

    private:
        glm::vec3 position;
        float height;
        std::vector<ShapeVertex> m_vertices;        
        GLsizei m_nVertexCount;
    };
    
}