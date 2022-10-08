#include "Collision_test_world.h"
#include "Core/Engine.h"

int main()
{
    MEngine::Engine engine;
    engine.set_window_title("Collision test");
    engine.set_default_world(Collision_test_world::static_class());
    engine.start();
}
