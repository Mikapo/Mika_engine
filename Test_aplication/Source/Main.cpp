#include "Core/Mika_engine.h"
#include "Test_world.h"

int WinMain()
{
    Mika_engine engine;
    engine.set_world<Test_world>();
    engine.start();
}
