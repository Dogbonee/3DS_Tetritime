//
// Created by hunde on 4/9/2024.
//

#ifndef BLITZGAME_H
#define BLITZGAME_H

#include "Game.h"


class BlitzGame : public Game
{

    dl::Text m_timeText;
    float m_elapsedTime;

public:
    BlitzGame(StateMachine &sm, dl::RenderWindow &window);

    void Update(const float &dt) override;
    void Render() override;
    void UpdateElapsedTime(const float &dt);
};


#endif //BLITZGAME_H
