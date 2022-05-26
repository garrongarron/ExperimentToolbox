#include "Etb.h"

using namespace etb;

class App : public Application {
public:
    App() : Application("Hello, ETB!", 1240, 720) {
    }
    
    void Tick() {

    }
};

int main(int argc, char* argv[]) {
    App app;
    app.Start();

    return 0;
}