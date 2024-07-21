//
// Created by minri on 3/25/2024.
//

#ifndef STATE_HPP
#define STATE_HPP

#include "System.h"


class StateMachine;

class State
{

protected:
    StateMachine* p_stateMachine;
    dl::RenderWindow* p_window;


    virtual void HandleButtonInput();

public:
    virtual ~State() = default;

    State(StateMachine &sm, dl::RenderWindow &window);
    virtual void Update(const float &dt) = 0;
    virtual void Render() = 0;
};


#endif //STATE_HPP
