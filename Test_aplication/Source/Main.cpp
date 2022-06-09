#include "Core/Mika_engine.h"
#include "Test_world.h"

int WinMain()
{
    Mika_engine engine;
    engine.set_window_title("Test scene");
    engine.set_default_world(Test_world::static_class());
    engine.start();
}
