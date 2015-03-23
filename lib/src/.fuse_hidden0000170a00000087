#include "Spray.hpp"

namespace glimac {
	void Spray::addDrop(glm::vec3 planePos){
		for (int i=0; i <= 10; ++i) {
			glm::vec2 disk = glm::diskRand(0.1f);
			positionArray.push_back(glm::vec3(disk[0],planePos[1]+glm::linearRand(0.f,0.1f),disk[1]));
			velocityArray.push_back(glm::vec3(0.1f+glm::linearRand(0.f,0.05f), 0.75f, 0.1f+glm::linearRand(0.f,0.05f)));
			massArray.push_back(glm::linearRand(0.9f,1.1f));
			forceArray.push_back(glm::vec3(0.f));	

			disk = glm::diskRand(0.05f);
			positionArray.push_back(glm::vec3(disk[0],planePos[1]+glm::linearRand(0.f,0.1f),disk[1]));
			velocityArray.push_back(glm::vec3(-0.1f+glm::linearRand(0.f,0.05f), 0.75f, 0.1f+glm::linearRand(0.f,0.05f)));
			massArray.push_back(glm::linearRand(0.9f,1.1f));
			forceArray.push_back(glm::vec3(0.f));	

			disk = glm::diskRand(0.05f);
			positionArray.push_back(glm::vec3(disk[0],planePos[1]+glm::linearRand(0.f,0.1f),disk[1]));
			velocityArray.push_back(glm::vec3(0.1f+glm::linearRand(0.f,0.05f), 0.75f, -0.1f+glm::linearRand(0.f,0.05f)));
			massArray.push_back(glm::linearRand(0.9f,1.1f));
			forceArray.push_back(glm::vec3(0.f));					

			disk = glm::diskRand(0.05f);
			positionArray.push_back(glm::vec3(disk[0],planePos[1]+glm::linearRand(0.f,0.1f),disk[1]));
			velocityArray.push_back(glm::vec3(-0.1f+glm::linearRand(0.f,0.05f), 0.75f, -0.1f+glm::linearRand(0.f,0.05f)));
			massArray.push_back(glm::linearRand(0.9f,1.1f));
			forceArray.push_back(glm::vec3(0.f));	

			disk = glm::diskRand(0.05f);
			positionArray.push_back(glm::vec3(disk[0],planePos[1]+glm::linearRand(0.f,0.1f),disk[1]));
			velocityArray.push_back(glm::vec3(-0.f+glm::linearRand(0.f,0.05f), 1.f, 0.f+glm::linearRand(0.f,0.05f)));
			massArray.push_back(glm::linearRand(0.9f,1.1f));
			forceArray.push_back(glm::vec3(0.f));
		}
	}

	void Spray::removeDrop(int index){
		positionArray.erase(positionArray.begin(), positionArray.begin()+1);
		velocityArray.erase(velocityArray.begin(), velocityArray.begin()+1);
		massArray.erase(massArray.begin(), massArray.begin()+1);
		forceArray.erase(forceArray.begin(), forceArray.begin()+1);
	}

	void Spray::update(float dt, Plane &plane) {
		for(int k=0; k < positionArray.size(); ++k) {
	        velocityArray[k] = velocityArray[k] + dt * forceArray[k]/massArray[k];
	        positionArray[k] += dt * velocityArray[k];
	        forceArray[k] = glm::vec3(0.f);

			if(positionArray[k][1] < plane.getPosition()[1]) {
				Force3D force;
				force.force = glm::vec3(0.f,-5.f,0.f);
    			force.position = positionArray[k];
				
				plane.applyExternalForce(force);
				removeDrop(k);
			}
		}
	}

	void Spray::applyGravity(Force3D force) {
		for(int k=0; k < forceArray.size(); ++k) {
			forceArray[k] += massArray[k]*force.force;
		}
	}

	void Spray::load(VAO &vao, VBO &vbo) {
        vbo.bind();
            glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(glm::vec3), getDataPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        vao.bind();
            glEnableVertexAttribArray(0);
            vbo.bind();
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

	void Spray::display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Uniforms &uniforms) {
        load(vao, vbo);
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uniforms.uDropMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uniforms.uDropNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uniforms.uDropMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

        glEnable(GL_POINT_SPRITE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        glPointSize(5);
        glDrawArrays(GL_POINTS, 0, getVertexCount());
        glDisable(GL_POINT_SPRITE);
	}
}