#include <cmath>
#include <vector>
#include <iostream>
#include "common.hpp"
#include "Fountain.hpp"

namespace glimac {

    void Fountain::build(float radius) {
        int nbSegments = 64;
        float step = 2 * glm::pi<float>()/nbSegments;
        for (int i=0; i< nbSegments; ++i){
            float c = cos(i*step);
            float s = sin(i*step);
            float cn = cos((i+1)*step);
            float sn = sin((i+1)*step);
            m_vertices.push_back(ShapeVertex(glm::vec3(0.f), glm::vec2(0.f,0.f), glm::vec3(0.f,-1.f,0.f)));
            m_vertices.push_back(ShapeVertex(glm::vec3(radius*c,0,radius*s), glm::vec2(0.f,1.f), glm::vec3(0.f,-1.f,0.f)));
            m_vertices.push_back(ShapeVertex(glm::vec3(radius*cn,0,radius*sn), glm::vec2(1.f,0.5f), glm::vec3(0.f,-1.f,0.f)));


            glm::vec3 A = glm::vec3(radius*c,0.f,radius*s); 
            glm::vec3 B = glm::vec3(radius*cn,0.f,radius*sn);
            glm::vec3 C = glm::vec3(radius*c,0.7f,radius*s);
            glm::vec3 D = glm::vec3(radius*cn,0.7f,radius*sn); 
            glm::vec3 E = glm::vec3((radius-1.f)*c,0.7f,(radius-1.f)*s); 
            glm::vec3 F = glm::vec3((radius-1.f)*cn,0.7f,(radius-1.f)*sn); 
            glm::vec3 G = glm::vec3((radius-1.f)*c,0.1f,(radius-1.f)*s); 
            glm::vec3 H = glm::vec3((radius-1.f)*cn,0.1f,(radius-1.f)*sn); 
            glm::vec3 I = glm::vec3(0.5f*c,0.1,0.5f*s); 
            glm::vec3 J = glm::vec3(0.5f*cn,0.1,0.5f*sn); 
            glm::vec3 K = glm::vec3(0.5f*c,0.7f,0.5f*s); 
            glm::vec3 L = glm::vec3(0.5f*cn,0.7f,0.5f*sn); 
            glm::vec3 M = glm::vec3(0.05f*c,0.7f,0.05f*s); 
            glm::vec3 N = glm::vec3(0.05f*cn,0.7f,0.05f*sn); 

            m_vertices.push_back(ShapeVertex(A, glm::vec2(0.f,0.f), glm::cross(B-A,B-C)));
            m_vertices.push_back(ShapeVertex(B, glm::vec2(0.f,1.f), glm::cross(B-A,B-C)));
            m_vertices.push_back(ShapeVertex(C, glm::vec2(1.f,0.f), glm::cross(B-A,B-C)));

            m_vertices.push_back(ShapeVertex(B, glm::vec2(0.f,1.f), glm::cross(B-C,B-D)));
            m_vertices.push_back(ShapeVertex(C, glm::vec2(1.f,0.f), glm::cross(B-C,B-D)));
            m_vertices.push_back(ShapeVertex(D, glm::vec2(1.f,1.f), glm::cross(B-C,B-D)));

            m_vertices.push_back(ShapeVertex(D, glm::vec2(0.f,0.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(E, glm::vec2(0.f,1.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(F, glm::vec2(1.f,0.f), glm::vec3(0.f,1.f,0.f)));

            m_vertices.push_back(ShapeVertex(C, glm::vec2(1.f,0.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(D, glm::vec2(0.f,0.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(E, glm::vec2(0.f,1.f), glm::vec3(0.f,1.f,0.f)));

            m_vertices.push_back(ShapeVertex(E, glm::vec2(0.f,1.f), glm::cross(F-E,F-G)));
            m_vertices.push_back(ShapeVertex(F, glm::vec2(1.f,0.f), glm::cross(F-E,F-G)));
            m_vertices.push_back(ShapeVertex(G, glm::vec2(1.f,1.f), glm::cross(F-E,F-G)));

            m_vertices.push_back(ShapeVertex(F, glm::vec2(1.f,0.f), glm::cross(F-G,F-H)));
            m_vertices.push_back(ShapeVertex(G, glm::vec2(1.f,1.f), glm::cross(F-G,F-H)));
            m_vertices.push_back(ShapeVertex(H, glm::vec2(0.f,0.f), glm::cross(F-G,F-H)));

            m_vertices.push_back(ShapeVertex(G, glm::vec2(0.f,0.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(H, glm::vec2(0.f,1.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(I, glm::vec2(1.f,0.f), glm::vec3(0.f,1.f,0.f)));

            m_vertices.push_back(ShapeVertex(H, glm::vec2(1.f,0.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(I, glm::vec2(0.f,0.f), glm::vec3(0.f,1.f,0.f)));
            m_vertices.push_back(ShapeVertex(J, glm::vec2(1.f,0.f), glm::vec3(0.f,1.f,0.f)));

            m_vertices.push_back(ShapeVertex(I, glm::vec2(0.f,1.f), glm::cross(J-I,J-K)));
            m_vertices.push_back(ShapeVertex(J, glm::vec2(1.f,0.f), glm::cross(J-I,J-K)));
            m_vertices.push_back(ShapeVertex(K, glm::vec2(1.f,1.f), glm::cross(J-I,J-K)));

            m_vertices.push_back(ShapeVertex(J, glm::vec2(1.f,0.f), glm::cross(J-K,J-L)));
            m_vertices.push_back(ShapeVertex(K, glm::vec2(1.f,1.f), glm::cross(J-K,J-L)));
            m_vertices.push_back(ShapeVertex(L, glm::vec2(0.f,0.f), glm::cross(J-K,J-L)));

            m_vertices.push_back(ShapeVertex(K, glm::vec2(0.f,1.f), glm::cross(L-K,L-M)));
            m_vertices.push_back(ShapeVertex(L, glm::vec2(1.f,0.f), glm::cross(L-K,L-M)));
            m_vertices.push_back(ShapeVertex(M, glm::vec2(1.f,1.f), glm::cross(L-K,L-M)));

            m_vertices.push_back(ShapeVertex(L, glm::vec2(1.f,0.f), glm::cross(L-M,L-N)));
            m_vertices.push_back(ShapeVertex(M, glm::vec2(1.f,1.f), glm::cross(L-M,L-N)));
            m_vertices.push_back(ShapeVertex(N, glm::vec2(0.f,0.f), glm::cross(L-M,L-N)));
        }
        m_nVertexCount = m_vertices.size();
    }

    void Fountain::load(VAO &vao, VBO &vbo) {
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

    void Fountain::display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light light) {
        load(vao, vbo);

        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniform3fv(uniforms.uFountainLightDirection, 1, glm::value_ptr(light.direction));
        glUniform3fv(uniforms.uFountainLightColor, 1, glm::value_ptr(light.color));
        glUniform3fv(uniforms.uFountainCameraPosition, 1, glm::value_ptr(light.cameraPosition));
        glUniform1f(uniforms.uFountainLightIntensity, light.intensity);
        glUniform1f(uniforms.uFountainSpecularPower, light.specularPower);

        glUniformMatrix4fv(uniforms.uFountainMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uniforms.uFountainNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uniforms.uFountainMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
      
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
        glUniform1i(uniforms.uFountainTexture,0);

    }
}