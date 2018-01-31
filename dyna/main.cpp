#include <iostream>
#include "Engine.h"

using namespace std;

int main(int argv, char** args) {
    Engine *engine = new Engine("Dyna Blaster");
    engine->init();
    engine->run();
    delete engine;
    return 0;
}
