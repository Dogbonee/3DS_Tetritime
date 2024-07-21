//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "System.h"


class GameOver : public dl::Drawable
{


public:
    GameOver();
    void SetGameOverScore(unsigned long score);
    void draw(const dl::Vector2f &viewOffset) const override;


    dl::Text GameoverText;
    dl::Text ScoreText;

};


#endif //GAMEOVER_H
