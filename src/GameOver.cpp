//
// Created by 24crickenbach on 3/26/2024.
//

#include "GameOver.h"

GameOver::GameOver() : GameoverText(TStaticBuffer), ScoreText(TStaticBuffer)
{

    GameoverText.setString("Game Over!");
    GameoverText.setPosition(System::WIDTH / 2, 100);

    ScoreText.setPosition(System::WIDTH / 2, System::HEIGHT / 2 + 20);
}

void GameOver::SetGameOverScore(unsigned long score)
{
    ScoreText.setString("Score: " + std::to_string(score));
}

void GameOver::draw(const dl::Vector2f &viewOffset) const
{
    GameoverText.draw(viewOffset);
    ScoreText.draw(viewOffset);
}


