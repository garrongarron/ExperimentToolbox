#include <GL/glew.h>
#include <fstream>

#include "Graphics.h"
#include "Debug.h"
#include "Shader.h"

etb::Shader::Shader() {
	// SetupHotReload();
}

etb::Shader::Shader(const char* path) {
	// SetupHotReload();
	LoadSources(path);
	Compile();
}

etb::Shader::~Shader() {
	glDeleteProgram(program);
}

std::string _LoadFile(const char* path) {
    try {
		std::stringstream buffer;
		std::ifstream file(path, std::ios::in);

        if (file.is_open()) {
			std::string contents = "";

			while (file.peek() != EOF)
			{
				contents += (char) file.get();
			}
			file.close();

            return contents;
        }
    }
    catch (const std::ifstream::failure& e) {
        etb::Debug::Print("Cannot open file \"" + std::string(path) + "\"");
    }

    return std::string("");
}

void PrintShaderLog(int shader) {
	if (glIsShader(shader)) {
		int infoLogLength = 0;
		int maxLength = infoLogLength;

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

void etb::Shader::LoadSources(const char* path) {
	this->path = path;
    fragSource = _LoadFile((std::string(path) + ".frag").c_str());
    vertSource = _LoadFile((std::string(path) + ".vert").c_str());
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
