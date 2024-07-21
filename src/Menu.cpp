//
// Created by 24crickenbach on 3/26/2024.
//

#include "Menu.h"

#include <iostream>

Menu::Menu(StateMachine &sm, dl::RenderWindow &window) : State(sm, window), m_textBuffer(4096),
                                                         m_titleLabel(m_textBuffer),
                                                         m_standardButton(dl::Vector2f(100, 60), "Play Standard"),
                                                         m_fLineButton(dl::Vector2f(100, 60), "Play 40 Lines"),
                                                         m_blitzButton(dl::Vector2f(100, 60), "Play Blitz")
{


    m_titleLabel.setString("Tetritime");
    m_titleLabel.setPosition(200, 100);
    m_titleLabel.setScale(dl::Vector2f(2.0, 2.0));

    m_standardButton.setPosition(100, 100);
    m_standardButton.setColor(dl::Color::Red);

    m_fLineButton.setPosition(System::WIDTH / 4, System::HEIGHT * 3 / 4);
    m_fLineButton.setColor(dl::Color::Blue);

    m_blitzButton.setPosition(225, System::HEIGHT * 3 / 4);
    m_blitzButton.setColor(dl::Color::Yellow);

    m_standardButton.callback = [this]
    { StartStandardGame(); };
    m_fLineButton.callback = [this]
    { StartFourtyLineGame(); };
    m_blitzButton.callback = [this]
    { StartBlitzGame(); };

    m_buttons.push_back(m_standardButton);
    m_buttons.push_back(m_fLineButton);
    m_buttons.push_back(m_blitzButton);

}

void Menu::StartStandardGame()
{
    p_stateMachine->SwitchState(GAME);
}


void Menu::StartFourtyLineGame()
{
    p_stateMachine->SwitchState(FLINE_GAME);
}

void Menu::StartBlitzGame()
{
    p_stateMachine->SwitchState(BLITZ_GAME);
}

void Menu::Render()
{

    p_window->clear(dl::TOP_SCREEN, dl::Color(180, 180, 180));
    p_window->draw(m_titleLabel);
    p_window->display();

    p_window->clear(dl::BOTTOM_SCREEN, dl::Color(180, 180, 180));
    for (auto &button: m_buttons) p_window->draw(button);
    p_window->display();
}


void Menu::Update(const float &dt)
{
    Render();
    for (auto &button: m_buttons)
    {
        button.ButtonUpdate();
    }
}


