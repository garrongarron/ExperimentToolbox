#include <fstream>

#include "File.h"
#include "../Core/Debug.h"

etb::File::File(const std::string& _path) {
    std::ifstream file(_path, std::ios::in);
}

etb::File::~File() {
}

std::string etb::File::ReadLine() {
    std::string line;
    std::getline(file, line);
    return line;
}

void etb::File::Close() {
    file.close();
}

bool etb::File::Exists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

std::string etb::File::ReadAll(const std::string& path) {
    try {
        std::stringstream buffer;
        std::ifstream file(path, std::ios::in);

        if (file.is_open()) {
            std::string contents = "";

            while (file.peek() != EOF)
            {
                contents += (char)file.get();
            }
            file.close();

            return contents;
        }
    }
    catch (const std::ifstream::failure& e) {
        etb::Debug::Print("Cannot read file \"" + std::string(path) + "\"");
    }

    return std::string();
}
