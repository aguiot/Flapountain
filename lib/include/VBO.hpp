#pragma once

#include <GL/glew.h>

namespace glimac {

class VBO {
public:
	VBO() {
		glGenBuffers(1, &m_nGLId);
	}

	~VBO() {
		glDeleteBuffers(1, &m_nGLId);
	}

	VBO(VBO&& rvalue): m_nGLId(rvalue.m_nGLId) {
		rvalue.m_nGLId = 0;
	}

	VBO& operator =(VBO&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const {
		return m_nGLId;
	}

	void bind(GLenum target = GL_ARRAY_BUFFER) const {
		glBindBuffer(target, m_nGLId);
	}

    static void unbind(GLenum target = GL_ARRAY_BUFFER) {
        glBindBuffer(target, 0);
    }
    	
private:
	VBO(const VBO& value);
	VBO& operator =(const VBO&);

	GLuint m_nGLId;
};

}
