#include "Etb.h"

using namespace etb;

class App : public Application {
public:
    glm::vec3 rot{ 0.0f };
    Shader shader;
    Material mat;
    Texture tex;

    App() : Application("Hello, ETB!", 1240, 720), tex("Assets/test.png") {
        Graphics::GL::ClearColor({ 0, 0, 0 });

        shader.LoadSources("Build-In/Shaders/Lit");
        shader.Compile();   
        shader.HotReload();

        mat.SetShader(&shader);
    }

    void Update() {
    }

    void Render() {
        Graphics::GL::Perspective(45, 1240 / 720.0f, 0.1f, 100.0f);

        glTranslatef(0, 0, -4);

        mat.Use();
        // mat.SetSampler2D("texture", tex);
        Graphics::DrawMesh(Primitives::cube, { 0, 0, -4 }, rot);
    }

    void GUI() {
        ImGui::Begin("World Config");

        ImGui::DragFloat3("Spawn Size", &rot[0], 0.1f, -180.0f, 180.0f);

        ImGui::End();
    }
};

int main(int argc, char* argv[]) {
    App app;
    app.Start();

    return 0;
}