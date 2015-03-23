#include <cmath>
#include <vector>
#include <iostream>
#include "common.hpp"
#include "Pipe.hpp"

namespace glimac {

    void Pipe::build(float radius) {
        float r = radius/5.f;
        int nbSegments = 64;
        float step = 2 * glm::pi<float>()/nbSegments;
        height = rand()%4;
        for (int i=0; i< nbSegments; ++i){
            float c = cos(i*step);
            float s = sin(i*step);
            float cn = cos((i+1)*step);
            float sn = sin((i+1)*step);
            m_vertices.push_back(ShapeVertex(glm::vec3(0.f), glm::vec2(0.f,0.f), glm::vec3(0.f,-1.f,0.f)));
            m_vertices.push_back(ShapeVertex(glm::vec3(r*c,0,r*s), glm::vec2(0.f,1.f), glm::vec3(0.f,-1.f,0.f)));
            m_vertices.push_back(ShapeVertex(glm::vec3(r*cn,0,r*sn), glm::vec2(1.f,0.5f), glm::vec3(0.f,-1.f,0.f)));


            glm::vec3 A = position + glm::vec3(r*c,0.f,r*s); 
            glm::vec3 B = position + glm::vec3(r*cn,0.f,r*sn);
            glm::vec3 C = position + glm::vec3(r*c,height+2.f,r*s);
            glm::vec3 D = position + glm::vec3(r*cn,height+2.f,r*sn);
            glm::vec3 E = position + glm::vec3((r+0.3f)*c,height+2.f,(r+0.3f)*s);
            glm::vec3 F = position + glm::vec3((r+0.3f)*cn,height+2.f,(r+0.3f)*sn);
            glm::vec3 G = position + glm::vec3((r+0.3f)*c,height+3.f,(r+0.3f)*s);
            glm::vec3 H = position + glm::vec3((r+0.3f)*cn,height+3.f,(r+0.3f)*sn);
            glm::vec3 I = position + glm::vec3((r-0.1f)*c,height+3.f,(r-0.1f)*s);
            glm::vec3 J = position + glm::vec3((r-0.1f)*cn,height+3.f,(r-0.1f)*sn);
            glm::vec3 K = position + glm::vec3((r-0.1f)*c,0.1f,(r-0.1f)*s);
            glm::vec3 L = position + glm::vec3((r-0.1f)*cn,0.1f,(r-0.1f)*sn);
            glm::vec3 M = position + glm::vec3(0.f,0.1f,0.f);

            m_vertices.push_back(ShapeVertex(A, glm::vec2(0.f), glm::cross(B-A,B-C)));
            m_vertices.push_back(ShapeVertex(B, glm::vec2(0.f), glm::cross(B-A,B-C)));
            m_vertices.push_back(ShapeVertex(C, glm::vec2(0.f), glm::cross(B-A,B-C)));

            m_vertices.push_back(ShapeVertex(B, glm::vec2(0.f), glm::cross(B-C,B-D)));
            m_vertices.push_back(ShapeVertex(C, glm::vec2(0.f), glm::cross(B-C,B-D)));
            m_vertices.push_back(ShapeVertex(D, glm::vec2(0.f), glm::cross(B-C,B-D)));

            m_vertices.push_back(ShapeVertex(C, glm::vec2(0.f), glm::cross(D-C,D-E)));
            m_vertices.push_back(ShapeVertex(D, glm::vec2(0.f), glm::cross(D-C,D-E)));
            m_vertices.push_back(ShapeVertex(E, glm::vec2(0.f), glm::cross(D-C,D-E)));

            m_vertices.push_back(ShapeVertex(D, glm::vec2(0.f), glm::cross(D-E,D-F)));
            m_vertices.push_back(ShapeVertex(E, glm::vec2(0.f), glm::cross(D-E,D-F)));
            m_vertices.push_back(ShapeVertex(F, glm::vec2(0.f), glm::cross(D-E,D-F)));

            m_vertices.push_back(ShapeVertex(E, glm::vec2(0.f), glm::cross(F-E,F-G)));
            m_vertices.push_back(ShapeVertex(F, glm::vec2(0.f), glm::cross(F-E,F-G)));
            m_vertices.push_back(ShapeVertex(G, glm::vec2(0.f), glm::cross(F-E,F-G)));

            m_vertices.push_back(ShapeVertex(F, glm::vec2(0.f), glm::cross(F-G,F-H)));
            m_vertices.push_back(ShapeVertex(G, glm::vec2(0.f), glm::cross(F-G,F-H)));
            m_vertices.push_back(ShapeVertex(H, glm::vec2(0.f), glm::cross(F-G,F-H)));

            m_vertices.push_back(ShapeVertex(G, glm::vec2(0.f), glm::cross(H-G,H-I)));
            m_vertices.push_back(ShapeVertex(H, glm::vec2(0.f), glm::cross(H-G,H-I)));
            m_vertices.push_back(ShapeVertex(I, glm::vec2(0.f), glm::cross(H-G,H-I)));

            m_vertices.push_back(ShapeVertex(H, glm::vec2(0.f), glm::cross(H-I,H-J)));
            m_vertices.push_back(ShapeVertex(I, glm::vec2(0.f), glm::cross(H-I,H-J)));
            m_vertices.push_back(ShapeVertex(J, glm::vec2(0.f), glm::cross(H-I,H-J)));

            m_vertices.push_back(ShapeVertex(I, glm::vec2(0.f), glm::cross(J-I,J-K)));
            m_vertices.push_back(ShapeVertex(J, glm::vec2(0.f), glm::cross(J-I,J-K)));
            m_vertices.push_back(ShapeVertex(K, glm::vec2(0.f), glm::cross(J-I,J-K)));

            m_vertices.push_back(ShapeVertex(J, glm::vec2(0.f), glm::cross(J-K,J-L)));
            m_vertices.push_back(ShapeVertex(K, glm::vec2(0.f), glm::cross(J-K,J-L)));
            m_vertices.push_back(ShapeVertex(L, glm::vec2(0.f), glm::cross(J-K,J-L)));

            m_vertices.push_back(ShapeVertex(K, glm::vec2(0.f), glm::vec3(0.f)));
            m_vertices.push_back(ShapeVertex(L, glm::vec2(0.f), glm::vec3(0.f)));
            m_vertices.push_back(ShapeVertex(M, glm::vec2(0.f), glm::vec3(0.f)));
        }
        m_nVertexCount = m_vertices.size();
    }

    void Pipe::load(VAO &vao, VBO &vbo) {
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

    void Pipe::display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light light) {
        load(vao, vbo);

        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniform3fv(uniforms.uPipeLightDirection, 1, glm::value_ptr(light.direction));
        glUniform3fv(uniforms.uPipeLightColor, 1, glm::value_ptr(light.color));
        glUniform3fv(uniforms.uPipeCameraPosition, 1, glm::value_ptr(light.cameraPosition));
        glUniform1f(uniforms.uPipeLightIntensity, light.intensity);
        glUniform1f(uniforms.uPipeSpecularPower, light.specularPower);

        glUniformMatrix4fv(uniforms.uPipeMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uniforms.uPipeNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uniforms.uPipeMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
      
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
        glUniform1i(uniforms.uPipeTexture,0);

    }
}