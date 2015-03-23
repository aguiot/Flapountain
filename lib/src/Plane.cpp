#include <cmath>
#include <vector>
#include <iostream>
#include "common.hpp"
#include "Plane.hpp"

float epsilon = 0.1f;

namespace glimac {

    void Plane::build() {
        planeWidth = 2*radius*5 + 1;

        L0.x = (2*radius - 0.2f) / (planeWidth - 2);
        L0.y = (2*radius - 0.2f) / (planeWidth - 2);
        L1 = glm::length(L0);
        L2 = 2.f * L0;

        K0 = 0.1f;
        K1 = 0.1f;
        K2 = 0.1f;

        V0 = 0.001f;
        V1 = 0.0001f;
        V2 = 0.0001f;

        for(float y = -radius; y <= radius; y+=0.2f) {
            for(float x = -radius; x <= radius; x+=0.2f) {
                positionArray.push_back(glm::vec3(x,0,y));       
                velocityArray.push_back(glm::vec3(0.f));
                massArray.push_back(1.f);
                forceArray.push_back(glm::vec3(0.f));        
            }
        }

        posToVertices();

        m_nVertexCount = m_vertices.size();

    }

    void Plane::posToVertices() {
        m_vertices.clear();
        for(float i = 0; i < planeWidth-1; ++i) {
            float offset = i * planeWidth;
            for(float j = 0; j < planeWidth-1; ++j) {

                glm::vec3 A = position + positionArray[offset + j];
                glm::vec3 B = position + positionArray[offset + (j + 1)];
                glm::vec3 C = position + positionArray[offset + planeWidth + 1 + (j + 1)];
                glm::vec3 D = position + positionArray[offset + j + planeWidth + 1];

                if(std::pow(positionArray[offset + j][0], 2) + std::pow(positionArray[offset + j][2], 2) <= std::pow(radius-epsilon,2) &&
                   std::pow(positionArray[offset + (j + 1)][0], 2) + std::pow(positionArray[offset + (j + 1)][2], 2) <= std::pow(radius,2) &&
                   std::pow(positionArray[offset + planeWidth + 1 + (j + 1)][0], 2) + std::pow(positionArray[offset + planeWidth + 1 + (j + 1)][2], 2) <= std::pow(radius,2)) {
                    
                    m_vertices.push_back(ShapeVertex(A, glm::vec2(0.f,0.f), glm::cross(B-A,B-C)));
                    m_vertices.push_back(ShapeVertex(B, glm::vec2(1.f,0.f), glm::cross(B-A,B-C)));
                    m_vertices.push_back(ShapeVertex(C, glm::vec2(1.f,1.f), glm::cross(B-A,B-C)));
                }

                if(std::pow(positionArray[offset + j][0], 2) + std::pow(positionArray[offset + j][2], 2) <= std::pow(radius,2) &&
                   std::pow(positionArray[offset + planeWidth + 1 + (j + 1)][0], 2) + std::pow(positionArray[offset + planeWidth + 1 + (j + 1)][2], 2) <= std::pow(radius-epsilon,2) &&
                   std::pow(positionArray[offset + j + planeWidth + 1][0], 2) + std::pow(positionArray[offset + j + planeWidth + 1][2], 2) <= std::pow(radius,2)){
                    
                    m_vertices.push_back(ShapeVertex(A, glm::vec2(0.f,0.f), glm::cross(C-A,C-D)));
                    m_vertices.push_back(ShapeVertex(C, glm::vec2(1.f,1.f), glm::cross(C-A,C-D)));
                    m_vertices.push_back(ShapeVertex(D, glm::vec2(0.f,1.f), glm::cross(C-A,C-D)));
                }
            }
        }
    }

    void Plane::load(VAO &vao, VBO &vbo) {
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

    void Plane::display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uniforms &uniforms, Light &light) {
        posToVertices();
        load(vao, vbo);

        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniform3fv(uniforms.uPlaneLightDirection, 1, glm::value_ptr(light.direction));
        glUniform3fv(uniforms.uPlaneLightColor, 1, glm::value_ptr(light.color));
        glUniform3fv(uniforms.uPlaneCameraPosition, 1, glm::value_ptr(light.cameraPosition));
        glUniform1f(uniforms.uPlaneLightIntensity, light.intensity);
        glUniform1f(uniforms.uPlaneSpecularPower, light.specularPower);

        glUniform1f(uniforms.uPlaneRadius, radius);
        glUniformMatrix4fv(uniforms.uPlaneMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uniforms.uPlaneNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uniforms.uPlaneMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        

        glBindTexture(GL_TEXTURE_2D, texture.texture);        
        glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
        glUniform1i(uniforms.uPlaneTexture,0);

    }

    void Plane::update(float dt) {
        for(int k = 0; k < positionArray.size(); ++k) {
            velocityArray[k] = velocityArray[k] + dt * forceArray[k]/massArray[k];
            positionArray[k][1] += dt * velocityArray[k][1];
            positionArray[k][1] = clamp(positionArray[k][1], 0.11f - position[1], 0.69f - position[1]);
            forceArray[k] = glm::vec3(0.f);
        } 
    }

    void Plane::applyInternalForces(float dt) {

        for(int j = 0; j < planeWidth; ++j) {
            for(int i = 0; i < planeWidth; ++i) {
                int k = i + j * (planeWidth);
                
                if (k%planeWidth == 0) continue;
                if ((k+1)%planeWidth == 0) continue;
                if (k >= planeWidth*(planeWidth-1)) continue;
                if (k < planeWidth) continue;
                if(std::pow(positionArray[k][0],2) + std::pow(positionArray[k][2],2) >= std::pow(radius,2)) continue;

                glm::vec3 force(0.f);
                
                // TOPOLOGIE 0
                if ((k+1)%planeWidth != 0) {
                    force += hookForce(K0, L0.x, positionArray[k], positionArray[k+1]);
                    force += brakeForce(V0, dt, velocityArray[k], velocityArray[k+1]);
                }
                if (k < planeWidth*(planeWidth-1)) {
                    force += hookForce(K0, L0.y, positionArray[k], positionArray[k+planeWidth]);
                    force += brakeForce(V0, dt, velocityArray[k], velocityArray[k+planeWidth]);
                }
                if (k > planeWidth-1) {
                    force += hookForce(K0, L0.y, positionArray[k], positionArray[k-planeWidth]); 
                    force += brakeForce(V0, dt, velocityArray[k], velocityArray[k-planeWidth]);
                }
                if (k%planeWidth != 0) {
                    force += hookForce(K0, L0.x, positionArray[k], positionArray[k-1]); 
                    force += brakeForce(V0, dt, velocityArray[k], velocityArray[k-1]);
                }

                // TOPOLOGIE 1
                if ((k+1)%planeWidth != 0 && k < planeWidth*(planeWidth-1)) {
                    force += hookForce(K1, L1, positionArray[k], positionArray[k+planeWidth+1]);
                    force += brakeForce(V1, dt, velocityArray[k], velocityArray[k+planeWidth+1]);
                }
                if ((k+1)%planeWidth != 0 && k > planeWidth) {
                    force += hookForce(K1, L1, positionArray[k], positionArray[k-planeWidth+1]);
                    force += brakeForce(V1, dt, velocityArray[k], velocityArray[k-planeWidth+1]);
                }
                if (k%planeWidth != 0 && k < planeWidth*(planeWidth-1)) {
                    force += hookForce(K1, L1, positionArray[k], positionArray[k+planeWidth-1]);
                    force += brakeForce(V1, dt, velocityArray[k], velocityArray[k+planeWidth-1]);
                }
                if (k%planeWidth != 0 && k > planeWidth) {
                    force += hookForce(K1, L1, positionArray[k], positionArray[k-planeWidth-1]);
                    force += brakeForce(V1, dt, velocityArray[k], velocityArray[k-planeWidth-1]);
                }
            
                // TOPOLOGIE 2
                if ((k+1)%planeWidth != 0 && (k+2)%planeWidth != 0) {
                    force += hookForce(K2, L2.x, positionArray[k], positionArray[k+2]);
                    force += brakeForce(V2, dt, velocityArray[k], velocityArray[k+2]);
                }
                if (k < planeWidth*(planeWidth-2)) {
                    force += hookForce(K2, L2.y, positionArray[k], positionArray[k+2*planeWidth]);
                    force += brakeForce(V2, dt, velocityArray[k], velocityArray[k+2*planeWidth]);
                }
                if (k > 2*planeWidth) {
                    force += hookForce(K2, L2.y, positionArray[k], positionArray[k-2*planeWidth]); 
                    force += brakeForce(V2, dt, velocityArray[k], velocityArray[k-2*planeWidth]);
                }
                if (k%planeWidth != 0 && (k-1)%planeWidth != 0) {
                    force += hookForce(K2, L2.x, positionArray[k], positionArray[k-2]); 
                    force += brakeForce(V2, dt, velocityArray[k], velocityArray[k-2]);
                }

                forceArray[k] += force;
            }
        }
    }

    void Plane::applyExternalForce(Force3D force) {
        for(int k = 0; k < positionArray.size(); ++k) {
            if (positionArray[k] == force.position) {
                forceArray[k] += force.force;
            }
        }
    }
}