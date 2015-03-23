#include "Skybox.hpp"

namespace glimac {

    void Skybox::load(VAO &vao, VBO &vbo) {
        vbo.bind();
            glBufferData(GL_ARRAY_BUFFER, shape.getVertexCount() * sizeof(ShapeVertex), shape.getDataPointer(), GL_STATIC_DRAW);
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

    void Skybox::display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Texture texture, Uint32 tStart, Uniforms &uniforms, Light &light) {
        load(vao, vbo);
        // float revolutionSpeed = (float)tStart / 200;
        // MVMatrix = glm::rotate(MVMatrix, degreesToRadians(revolutionSpeed), glm::vec3(0.f,1.f,0.f));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // glm::vec4 pos = - glm::vec4(light.direction,1.f);
        // pos = pos * glm::rotate(glm::mat4(1.f), degreesToRadians(revolutionSpeed*0.1f), glm::vec3(0.f,1.f,0.f));
        // light.direction = - glm::vec3(pos);

        glUniformMatrix4fv(uniforms.uSkyboxMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uniforms.uSkyboxNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uniforms.uSkyboxMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glDrawArrays(GL_TRIANGLES, 0, shape.getVertexCount());
        glUniform1i(uniforms.uSkyboxTexture,0);

    }
}