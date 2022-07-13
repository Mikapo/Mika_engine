#include "Collision_test_world.h"
#include "Core/Mika_engine.h"

int WinMain()
{
    Mika_engine engine;
    engine.set_window_title("Collision test");
    engine.set_default_world(Collision_test_world::static_class());
    engine.start();
}
