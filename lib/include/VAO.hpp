#pragma once

#include <GL/glew.h>

namespace glimac {

class VAO {
public:
	VAO() {
		glGenBuffers(1, &m_nGLId);
	}

	~VAO() {
		glDeleteBuffers(1, &m_nGLId);
	}

	VAO(VAO&& rvalue): m_nGLId(rvalue.m_nGLId) {
		rvalue.m_nGLId = 0;
	}

	VAO& operator =(VAO&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const {
		return m_nGLId;
	}

	void bind() const {
		glBindVertexArray(m_nGLId);
	}

    static void unbind() {
        glBindVertexArray(0);
    }
    
private:
	VAO(const VAO& value);
	VAO& operator =(const VAO&);

	GLuint m_nGLId;
};

}
