//
// Created by hunde on 4/9/2024.
//

#include "BlitzGame.h"

BlitzGame::BlitzGame(StateMachine &sm, dl::RenderWindow &window) : Game(sm, window), m_timeText(TDynamicBuffer)
{

    m_timeText.setString("0:00:00");
    m_timeText.setPosition(15, 180);
    m_timeText.setAlignment(dl::AlignLeft);


    m_elapsedTime = 120;
}

void BlitzGame::Update(const float &dt)
{
    TDynamicBuffer.flushBuffer();
    Game::Update(dt);
    UpdateElapsedTime(dt);
    if (m_elapsedTime <= 0)
    {
        m_gameOverScreen.GameoverText.setString("Game End");
        m_gameOverScreen.SetGameOverScore(m_score);
        m_isGameOver = true;
    }

}

void BlitzGame::Render()
{
    p_window->clear(dl::TOP_SCREEN, dl::Color(180, 180, 180));


    if (m_isGameOver)
    {
        p_window->draw(m_gameOverScreen);
        p_window->display();
        return;
    }


    p_window->draw(m_board);
    p_window->draw(m_currentPiece);
    p_window->draw(m_nextPiece);
    p_window->draw(m_scoreLabel);
    p_window->draw(m_scoreText);

    p_window->draw(m_nextLabel);


    if (m_currentPiece.GetPosition() != m_ghostPiece.GetPosition())
    {
        p_window->draw(m_ghostPiece);
    }

    if (!m_isGameOver)
    {
        p_window->draw(m_timeText);
    }

    p_window->display();

    p_window->clear(dl::BOTTOM_SCREEN, dl::Color(180, 180, 180));
    p_window->draw(m_menuButton);
    p_window->draw(m_holdLabel);
    if (m_hasHeld)
    {
        p_window->draw(m_holdPiece);
    }

    p_window->display();

}

void BlitzGame::UpdateElapsedTime(const float &dt)
{
    m_elapsedTime -= dt;
    int minutes = static_cast<int>(m_elapsedTime) / 60;
    int seconds = static_cast<int>(m_elapsedTime) % 60;
    int millis = static_cast<int>((m_elapsedTime - (static_cast<float>(seconds) + minutes * 60)) * 100.f);
    m_timeText.setString(std::to_string(minutes) + ':' + (seconds < 10 ? "0" : "")
                         + std::to_string(seconds) + ':' + (millis < 10 ? "0" : "") + std::to_string(millis));
}
