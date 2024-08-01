//
// Created by minri on 3/25/2024.
//

#include "StateMachine.h"

#include <iostream>


StateMachine::StateMachine() : m_dt(0), m_shouldGameReset(false)
{
    m_gameMusic.loadFromFile("romfs:/music.opus");
    m_gameMusic.setLooping(true);
    m_window.set3dActive(true);
}

StateMachine::~StateMachine()
{

}


void StateMachine::UpdateState()
{

    //Only updates one state at any given point: the current state selected. Rendering and
    //Event handling are each handled separately by each state, not in the state machine.
    while (m_window.isOpen())
    {
        m_dt = m_clock.restart().asSeconds();
        if (p_currentState != nullptr)
        {
            if (m_shouldGameReset)
            {
                //Kinda inefficient but whatever
                m_states[GAME].reset();
                m_states[GAME] = std::make_shared<Game>(*this, m_window);
                m_states[FLINE_GAME].reset();
                m_states[FLINE_GAME] = std::make_shared<FLineGame>(*this, m_window);
                m_states[BLITZ_GAME].reset();
                m_states[BLITZ_GAME] = std::make_shared<BlitzGame>(*this, m_window);
                m_shouldGameReset = false;
            }

            p_currentState->Update(m_dt);


        }
    }
}


void StateMachine::Run()
{
    m_gameMusic.play();
    UpdateState();
}

void StateMachine::AddState()
{
    //All possible states should be added here
    auto menu = std::make_shared<Menu>(*this, m_window);
    m_states.emplace_back(menu);
    auto game = std::make_shared<Game>(*this, m_window);
    m_states.emplace_back(game);
    auto fLineGame = std::make_shared<FLineGame>(*this, m_window);
    m_states.emplace_back(fLineGame);
    auto blitzGame = std::make_shared<BlitzGame>(*this, m_window);
    m_states.emplace_back(blitzGame);
}

void StateMachine::ResetGame()
{
    m_shouldGameReset = true;
}

void StateMachine::SwitchState(StateName state)
{

    //get a pointer to the selected state and set it as the current state
    p_currentState = m_states[state];


}
