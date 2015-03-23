#pragma once

#include <vector>

#include "common.hpp"
#include "Texture.hpp"

namespace glimac {

class Plane {
    void build();

    public:
        Plane(GLfloat radius, glm::vec3 position): m_nVertexCount(0), position(position), radius(radius) {
            build();
        }

        const ShapeVertex* getDataPointer() const {
            return &m_vertices[0];
        }
        
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

        glm::vec3 getPosition() {
            return position;
        }

        void posToVertices();
        void load(VAO &vao, VBO &vbo);
        void display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &Uniforms, Light &light);
        void update(float dt);
        void applyInternalForces(float dt);
        void applyExternalForce(Force3D force);

    private:
        std::vector<ShapeVertex> m_vertices;
        std::vector<glm::vec3> positionArray;
        std::vector<glm::vec3> velocityArray;
        std::vector<float> massArray;
        std::vector<glm::vec3> forceArray;

        int planeWidth;
        float radius;
        glm::vec3 position;

        glm::vec2 L0;
        float L1;
        glm::vec2 L2;

        float K0, K1, K2;
        float V0, V1, V2;
        
        GLsizei m_nVertexCount;
    };
    
}