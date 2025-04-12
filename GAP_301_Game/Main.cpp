#include "../Engine/system.h"
#include "../Engine/GameObject.h"
#include "../BLD/BleachNew.h"

int main()
{
    BLEACH_INIT_LEAK_DETECTOR();

    // Push all into engine
    Engine::System system;
    system.Inialize("Tron", 480, 480);
    system.Run();
    
    BLEACH_DUMP_AND_DESTROY_LEAK_DETECTOR();
    return 0;
}