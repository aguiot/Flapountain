#include <cmath>
#include <vector>
#include <iostream>
#include "common.hpp"
#include "Ground.hpp"

namespace glimac {

    void Ground::build(float radius) {
        m_vertices.push_back(ShapeVertex(glm::vec3(-radius,0.f,-radius), glm::vec2(0.f,0.f), glm::vec3(0.f,1.f,0.f)));
        m_vertices.push_back(ShapeVertex(glm::vec3(-radius,0.f,radius), glm::vec2(0.f,radius), glm::vec3(0.f,1.f,0.f)));
        m_vertices.push_back(ShapeVertex(glm::vec3(radius,0.f,-radius), glm::vec2(radius,0.f), glm::vec3(0.f,1.f,0.f)));

        m_vertices.push_back(ShapeVertex(glm::vec3(-radius,0.f,radius), glm::vec2(0.f,radius), glm::vec3(0.f,1.f,0.f)));
        m_vertices.push_back(ShapeVertex(glm::vec3(radius,0.f,radius), glm::vec2(radius,radius), glm::vec3(0.f,1.f,0.f)));
        m_vertices.push_back(ShapeVertex(glm::vec3(radius,0.f,-radius), glm::vec2(radius,0.f), glm::vec3(0.f,1.f,0.f)));

        m_nVertexCount = m_vertices.size();
    }

    void Ground::load(VAO &vao, VBO &vbo) {
        vbo.bind();
            glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        vao.bind();
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            vbo.bind();
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Ground::display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light light) {
        load(vao, vbo);

        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniform3fv(uniforms.uGroundLightDirection, 1, glm::value_ptr(light.direction));
        glUniform3fv(uniforms.uGroundLightColor, 1, glm::value_ptr(light.color));
        glUniform3fv(uniforms.uGroundCameraPosition, 1, glm::value_ptr(light.cameraPosition));
        glUniform1f(uniforms.uGroundLightIntensity, light.intensity);
        glUniform1f(uniforms.uGroundSpecularPower, light.specularPower);

        glUniformMatrix4fv(uniforms.uGroundMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uniforms.uGroundNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uniforms.uGroundMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
      
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
        glUniform1i(uniforms.uGroundTexture,0);

    }
}