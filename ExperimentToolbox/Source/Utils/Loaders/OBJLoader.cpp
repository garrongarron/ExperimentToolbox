

#include "OBJLoader.h"
#include "../../Core/Debug.h"
#include "../../IO/File.h"

etb::OBJFile::OBJFile(const std::string& _path) {
    if (!File::Exists(_path)) {
        Debug::Print("Import OBJ error: Couldn't import file \"" + _path + "\"");
        return;
    }
    
    path = _path;
}

etb::OBJFile::~OBJFile() {
}

etb::Mesh etb::OBJFile::GetMesh(const std::string& name) {
    Mesh tmp;
    Mesh mesh;

    std::ifstream file(path, std::ios::in);
    std::string header;

    bool objectExists = false;

    while (file >> header) {
        if (header == "o") {
            if (file >> header && header == name) {
                objectExists = true;
                break;
            }
        }
    }

    if (!objectExists) return mesh;

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ssLine(line);

        ssLine >> header >> std::ws;

        if (header == "o") {
            break;
        }
        else if (header == "v") {
            glm::vec3 v;
            ssLine >> v.x >> v.y >> v.z;
            tmp.vertex.push_back({ v.x, v.y, v.z });
        }
        else if (header == "vn") {
            glm::vec3 vn;
            ssLine >> vn.x >> vn.y >> vn.z;
            tmp.normals.push_back(vn);
        }
        else if (header == "vt") {
            glm::vec3 vt;
            ssLine >> vt.x >> vt.y;
            tmp.uv.push_back(vt);
        }
        else if (header == "f") {
            int v, t, n;

            for (int32_t i = 0; !ssLine.eof() && ssLine.peek() != -1; i++) {
                ssLine >> v;
                
                if (ssLine.peek() == '/') {
                    ssLine.get();

                    if (ssLine.peek() == '/') {
                        ssLine.get();
                        ssLine >> n;

                        mesh.vertex.push_back(tmp.vertex[v - 1]);
                        mesh.uv.push_back({ 0, 0 });
                        mesh.normals.push_back(tmp.normals[n - 1]);
                    }
                    else {
                        ssLine >> t;

                        if (ssLine.peek() == '/') {
                            ssLine.get();
                            ssLine >> n;

                            mesh.vertex.push_back(tmp.vertex[v - 1]);
                            mesh.uv.push_back(tmp.uv[t - 1]);
                            mesh.normals.push_back(tmp.normals[n - 1]);
                        }
                    }
                }
            }
            
            const int32_t i = mesh.vertex.size();
            mesh.elements.push_back({ i - 3, i - 2, i - 1 });
        }
    }

    file.close();

    return mesh;
}
