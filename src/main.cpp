#include "StateMachine.h"

int main()
{

    StateMachine sm;
    sm.AddState();
    sm.SwitchState(MENU);
    sm.Run();
    return 0;
}
