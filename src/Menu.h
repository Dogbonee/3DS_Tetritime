//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "StateMachine.h"


class Menu : public State
{


    dl::TextBuffer m_textBuffer;
    dl::Text m_titleLabel;

    std::vector<Button> m_buttons;
    Button m_standardButton;
    Button m_fLineButton;
    Button m_blitzButton;

    void StartStandardGame();
    void StartFourtyLineGame();
    void StartBlitzGame();

protected:

    void Render() override;


public:
    Menu(StateMachine &sm, dl::RenderWindow &window);

    void Update(const float &dt) override;


};


#endif //MENU_H
