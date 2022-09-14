#include "Core/Engine.h"
#include "Test_world.h"

int main()
{
    Mika_engine::Engine engine;
    engine.set_window_title("Scene");
    engine.set_default_world(Test_world::static_class());
    engine.start();
}