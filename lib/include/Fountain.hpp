#pragma once

#include <vector>

#include "common.hpp"
#include "Texture.hpp"

namespace glimac {

class Fountain {
    void build(float radius);

    public:
        Fountain(float radius) {
            build(radius);
        }

        const ShapeVertex* getDataPointer() const {
            return &m_vertices[0];
        }
        
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

        void load(VAO &vao, VBO &vbo);
        void display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light light);

    private:
        std::vector<ShapeVertex> m_vertices;        
        GLsizei m_nVertexCount;
    };
    
}