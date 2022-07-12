#include "Collision_test_world.h"
#include "Core/Mika_engine.h"

int main()
{
    Mika_engine engine;
    engine.set_default_world(Collision_test_world::static_class());
    engine.start();
}
