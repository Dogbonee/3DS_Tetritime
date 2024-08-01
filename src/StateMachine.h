//
// Created by minri on 3/25/2024.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <Dualie/Audio/Music.hpp>
#include <Dualie/System/Clock.hpp>
#include <memory>
#include <vector>

#include "State.h"
#include "Game.h"
#include "BlitzGame.h"
#include "FLineGame.h"
#include "Menu.h"



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
    dl::Clock m_clock;
    dl::Music m_gameMusic;
    float m_dt;
    bool m_shouldGameReset;



    void UpdateState();



public:
    StateMachine();
    ~StateMachine();
    void Run();
    void SwitchState(StateName state);
    void AddState();
    void ResetGame();

};


#endif //STATEMACHINE_HPP
