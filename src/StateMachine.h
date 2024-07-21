//
// Created by minri on 3/25/2024.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>

#include "State.h"
#include "Game.h"
#include "BlitzGame.h"
#include "FLineGame.h"
#include "Menu.h"
#include <vector>


enum StateName : int
{

    MENU = 0,
    GAME,
    FLINE_GAME,
    BLITZ_GAME

};


class StateMachine
{

    std::shared_ptr<State> p_currentState;
    std::vector<std::shared_ptr<State>> m_states;

    dl::RenderWindow m_window;

    const float m_dt;

    void UpdateState();

    bool m_shouldGameReset;

public:
    StateMachine();
    ~StateMachine();
    void Run();
    void SwitchState(StateName state);
    void AddState();
    void ResetGame();

};


#endif //STATEMACHINE_HPP
