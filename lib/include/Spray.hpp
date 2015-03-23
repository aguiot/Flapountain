#pragma once

#include "common.hpp"
#include "Plane.hpp"

namespace glimac {
	class Spray {
        std::vector<glm::vec3> positionArray;
        std::vector<glm::vec3> velocityArray;
        std::vector<float> massArray;
        std::vector<glm::vec3> forceArray;

	    public:
	    	const glm::vec3* getDataPointer() const {
	            return &positionArray[0];
	        }
	        
	        GLsizei getVertexCount() const {
	            return positionArray.size();
	        }

	    	void addDrop(glm::vec3 planePos);
	    	void removeDrop(int index);
	    	void update(float dt, Plane &plane);
	    	void applyGravity(Force3D force);
	    	void load(VAO &vao, VBO &vbo);
	    	void display(VAO &vao, VBO &vbo, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, Uniforms &uniforms);
	};
}