#pragma once

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "VAO.hpp"
#include "VBO.hpp"

namespace glimac {

	class ShapeVertex {
		public:
		    glm::vec3 position;
	    	glm::vec3 normal;
	    	glm::vec2 texCoords;
		    ShapeVertex(glm::vec3 position, glm::vec2 texCoords, glm::vec3 normal) : position(position), texCoords(texCoords), normal(normal) {};
		    ShapeVertex();
	};

	struct Light {
	    glm::vec3 direction;
	    glm::vec3 color;
	    float intensity;
	    float specularPower;
	    glm::vec3 cameraPosition;

	};

	struct Uniforms {
	    GLint uPlaneMVMatrix;
	    GLint uPlaneMVPMatrix;
	    GLint uPlaneNormalMatrix;
	    GLint uPlaneTexture;
	    GLint uPlaneRadius;
	    GLint uPlaneLightDirection;
	    GLint uPlaneLightColor;
	    GLint uPlaneLightIntensity;
	    GLint uPlaneSpecularPower;
	    GLint uPlaneCameraPosition;
	    
	    GLint uDropMVMatrix;
	    GLint uDropMVPMatrix;
	    GLint uDropNormalMatrix;

	    GLint uFountainMVMatrix;
	    GLint uFountainMVPMatrix;
	    GLint uFountainNormalMatrix;
	    GLint uFountainTexture;
	    GLint uFountainLightDirection;
	    GLint uFountainLightColor;
	    GLint uFountainLightIntensity;
	    GLint uFountainSpecularPower;
	    GLint uFountainCameraPosition;

	    GLint uGroundMVMatrix;
	    GLint uGroundMVPMatrix;
	    GLint uGroundNormalMatrix;
	    GLint uGroundTexture;
	    GLint uGroundLightDirection;
	    GLint uGroundLightColor;
	    GLint uGroundLightIntensity;
	    GLint uGroundSpecularPower;
	    GLint uGroundCameraPosition;

	    GLint uSkyboxMVMatrix;
	    GLint uSkyboxMVPMatrix;
	    GLint uSkyboxNormalMatrix;
	    GLint uSkyboxTexture;

	    GLint uPipeMVMatrix;
	    GLint uPipeMVPMatrix;
	    GLint uPipeNormalMatrix;
	    GLint uPipeTexture;
	    GLint uPipeLightDirection;
	    GLint uPipeLightColor;
	    GLint uPipeLightIntensity;
	    GLint uPipeSpecularPower;
	    GLint uPipeCameraPosition;

	    GLint uFlappyMVMatrix;
	    GLint uFlappyMVPMatrix;
	    GLint uFlappyNormalMatrix;
	    GLint uFlappyTexture;
	    GLint uFlappyLightDirection;
	    GLint uFlappyLightColor;
	    GLint uFlappyLightIntensity;
	    GLint uFlappySpecularPower;
	    GLint uFlappyCameraPosition;
	    GLint uFlappyPosition;

	};

	inline float degreesToRadians(float degrees) {
		float pi = glm::pi<float>();
		return pi * degrees / 180.f;
	}

	struct Force3D {
		glm::vec3 force;
		glm::vec3 position;
	};

	inline glm::vec3 hookForce(float K, float L, const glm::vec3& P1, const glm::vec3& P2) {
	    static const float epsilon = 0.0001;
	    return K * (1-L/std::max(glm::length(P1 - P2), epsilon)) * (P2 - P1);
	}

	inline glm::vec3 brakeForce(float V, float dt, const glm::vec3& v1, const glm::vec3& v2) {
	    return V * (v2 - v1) / dt;
	}

	inline std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec) {
	    out << "[" << vec.x << ", " << vec.y << ", "<< vec.z << "]";
	    return out;
	}

	inline bool operator==(const glm::vec3 &vecA, const glm::vec3 &vecB) { 
		const double epsilion = 0.1;
		return fabs(vecA[0] -vecB[0]) < epsilion && fabs(vecA[1] -vecB[1]) < epsilion && fabs(vecA[2] -vecB[2]) < epsilion;
	} 

	template<typename T>
	T clamp(const T &val, const T &min, const T &max) {
	    return std::max(min, std::min(max, val));
	}
}
