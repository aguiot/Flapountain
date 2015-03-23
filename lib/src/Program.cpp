#include "Program.hpp"
#include <stdexcept>

namespace glimac {

bool Program::link() {
	glLinkProgram(m_nGLId);
	GLint status;
	glGetProgramiv(m_nGLId, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

const std::string Program::getInfoLog() const {
	GLint length;
	glGetProgramiv(m_nGLId, GL_INFO_LOG_LENGTH, &length);
	char* log = new char[length];
	glGetProgramInfoLog(m_nGLId, length, 0, log);
	std::string logString(log);
	delete [] log;
	return logString;
}

// Build a GLSL program from source code
Program buildProgram(const GLchar* vsSrc, const GLchar* fsSrc) {
	Shader vs(GL_VERTEX_SHADER);
	vs.setSource(vsSrc);

	if(!vs.compile()) {
		throw std::runtime_error("Compilation error for vertex shader: " + vs.getInfoLog());
	}

	Shader fs(GL_FRAGMENT_SHADER);
	fs.setSource(fsSrc);

	if(!fs.compile()) {
		throw std::runtime_error("Compilation error for fragment shader: " + fs.getInfoLog());
	}

	Program program;
	program.attachShader(vs);
	program.attachShader(fs);

	if(!program.link()) {
		throw std::runtime_error("Link error: " + program.getInfoLog());
	}

	return program;
}

// Build a GLSL program from source code
Program buildProgram(const GLchar* vsSrc, const GLchar* gsSrc, const GLchar* fsSrc) {
	Shader vs(GL_VERTEX_SHADER);
	vs.setSource(vsSrc);

	if(!vs.compile()) {
		throw std::runtime_error("Compilation error for vertex shader: " + vs.getInfoLog());
	}

	Shader fs(GL_FRAGMENT_SHADER);
	fs.setSource(fsSrc);

	if(!fs.compile()) {
		throw std::runtime_error("Compilation error for fragment shader: " + fs.getInfoLog());
	}

	Shader gs(GL_GEOMETRY_SHADER);
	gs.setSource(gsSrc);

	if(!gs.compile()) {
		throw std::runtime_error("Compilation error for geometry shader: " + gs.getInfoLog());
	}

	Program program;
	program.attachShader(vs);
	program.attachShader(fs);
	program.attachShader(gs);

	if(!program.link()) {
		throw std::runtime_error("Link error: " + program.getInfoLog());
	}

	return program;
}

// Load source code from files and build a GLSL program
Program loadProgram(const char* vsFile, const char* fsFile) {
	Shader vs = loadShader(GL_VERTEX_SHADER, vsFile);
	Shader fs = loadShader(GL_FRAGMENT_SHADER, fsFile);

	if(!vs.compile()) {
		throw std::runtime_error("Compilation error for vertex shader (from file " + std::string(vsFile) + "): " + vs.getInfoLog());
	}

	if(!fs.compile()) {
		throw std::runtime_error("Compilation error for fragment shader (from file " + std::string(fsFile) + "): " + fs.getInfoLog());
	}

	Program program;
	program.attachShader(vs);
	program.attachShader(fs);

	if(!program.link()) {
		throw std::runtime_error("Link error (for files " + std::string(vsFile) + " and " + fsFile + "): " + program.getInfoLog());
	}

	return program;
}

// Load source code from files and build a GLSL program
Program loadProgram(const char* vsFile, const char* gsFile, const char* fsFile) {
	Shader vs = loadShader(GL_VERTEX_SHADER, vsFile);
	Shader fs = loadShader(GL_FRAGMENT_SHADER, fsFile);
	Shader gs = loadShader(GL_GEOMETRY_SHADER, gsFile);

	if(!vs.compile()) {
		throw std::runtime_error("Compilation error for vertex shader (from file " + std::string(vsFile) + "): " + vs.getInfoLog());
	}

	if(!fs.compile()) {
		throw std::runtime_error("Compilation error for fragment shader (from file " + std::string(fsFile) + "): " + fs.getInfoLog());
	}

	if(!gs.compile()) {
		throw std::runtime_error("Compilation error for geometry shader (from file " + std::string(gsFile) + "): " + gs.getInfoLog());
	}


	Program program;
	program.attachShader(vs);
	program.attachShader(fs);
	program.attachShader(gs);

	if(!program.link()) {
		throw std::runtime_error("Link error (for files " + std::string(vsFile) + ", " + gsFile + " and " + fsFile + "): " + program.getInfoLog());
	}

	return program;
}

}