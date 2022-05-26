#include <GL/glew.h>
#include <fstream>

#include "Graphics.h"
#include "Debug.h"
#include "Shader.h"
#include "../IO/File.h"

etb::Shader::Shader() : program(0), vertMTime(0), fragMTime(0) {
	SetupHotReload();
}

etb::Shader::Shader(const char* path) : program(0), vertMTime(0), fragMTime(0) {
	SetupHotReload();
	LoadSources(path);
	Compile();
}

etb::Shader::~Shader() {
	glDeleteProgram(program);
}

void PrintShaderLog(int32_t shader) {
	if (glIsShader(shader)) {
		int32_t infoLogLength = 0;
		int32_t maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];

		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

		if (infoLogLength > 0) {
            etb::Debug::Print(infoLog);
		}

		delete[] infoLog;
	}
	else {
		std::string _log = "Name ";
		_log += std::to_string(shader);
		_log += " is not a shader";
		etb::Debug::Print(_log);
	}
}

void etb::Shader::LoadSources(const char* _path) {
	this->path = _path;

	std::string fragPath = path + ".frag";
	std::string vertPath = path + ".vert";

	if (!File::Exists(fragPath)) {
		Debug::Print("Fragment shader \"" + fragPath + "\" does not exists");
		return;
	}

	if (!File::Exists(vertPath)) {
		Debug::Print("Vertex shader \"" + vertPath + "\" does not exists");
		return;
	}

    fragSource = File::ReadAll(fragPath);
    vertSource = File::ReadAll(vertPath);
}

bool etb::Shader::Compile() {
	GLuint programId = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexShaderSource[] = { vertSource.c_str()};
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

	if (vShaderCompiled != GL_TRUE) {
		Debug::Print("Unable to compile vertex shader ");
		PrintShaderLog(vertexShader);

		glDeleteShader(vertexShader);
		return false;
	}

	glAttachShader(programId, vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentShaderSource[] = { fragSource.c_str() };
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);

	if (fShaderCompiled != GL_TRUE) {
		Debug::Print("Unable to compile fragment shader ");
		PrintShaderLog(fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return false;
	}

	glAttachShader(programId, fragmentShader);

	glLinkProgram(programId);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	program = programId;

	fragSource = "";
	vertSource = "";

	return true;
}

void etb::Shader::LoadBinary(const char* path) {
}

void etb::Shader::SaveBinary(const char* path) {
}

void etb::Shader::SetupHotReload() {
	EventSystem::AddEventListener(EventType::Tick, [&](Event& e) {
		std::string fragPath = std::string(path) + ".frag";
		std::string vertPath = std::string(path) + ".vert";

		bool reload = false;
		struct stat fileInfo;

		stat(fragPath.c_str(), &fileInfo);

		if (fragMTime != fileInfo.st_mtime) {
			reload = true;
			fragMTime = fileInfo.st_mtime;
		}

		stat(vertPath.c_str(), &fileInfo);

		if (vertMTime != fileInfo.st_mtime) {
			reload = true;
			vertMTime = fileInfo.st_mtime;
		}

		if (reload) {
			Debug::Print("--------------------------------------");
			Debug::Print("Shader hot reload \"" + path + "\"");

			Debug::Print("Loading sources");
			LoadSources(path.c_str());

			Debug::Print("Compiling");
			if (Compile()) {
				Debug::Print("Shader successful reloaded");
			}
		}
	});
}
