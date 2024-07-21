
//
// Created by hunde on 4/9/2024.
//

#include "FLineGame.h"

FLineGame::FLineGame(StateMachine &sm, dl::RenderWindow &window) : Game(sm, window), m_elapsedTime(0),
                                                                   m_lineCountText(TStaticBuffer),
                                                                   m_timeText(TDynamicBuffer)
{

    m_timeText.setString("0:00:00");
    m_timeText.setPosition(15, 180);
    m_timeText.setAlignment(dl::AlignLeft);

    m_lineCountText.setString("Lines: 0");
    m_lineCountText.setPosition(90, 60);
}

void FLineGame::Update(const float &dt)
{
    TDynamicBuffer.flushBuffer();
    Game::Update(dt);
    UpdateElapsedTime(dt);
}

void FLineGame::Render()
{
    p_window->clear(dl::TOP_SCREEN, dl::Color(180, 180, 180));


    if (m_isGameOver)
    {
        p_window->draw(m_gameOverScreen);
        p_window->display();
        return;
    }


    p_window->draw(m_board);
    if (m_currentPiece.GetPosition() != m_ghostPiece.GetPosition())
    {
        p_window->draw(m_ghostPiece);
    }
    p_window->draw(m_currentPiece);
    p_window->draw(m_nextPiece);
    p_window->draw(m_scoreLabel);
    p_window->draw(m_scoreText);

    p_window->draw(m_nextLabel);


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
    p_window->draw(m_lineCountText);
    p_window->display();

}

void FLineGame::HandleScoring()
{
    Game::HandleScoring();
    if (m_clearedLineCount >= 40)
    {
        m_gameOverScreen.GameoverText.setString("Game End");
        m_gameOverScreen.ScoreText.setString("Time: " + m_timeText.getString());
        m_isGameOver = true;
    }
    m_lineCountText.setString("Lines: " + std::to_string(m_clearedLineCount));
}

void FLineGame::UpdateElapsedTime(const float &dt)
{
    m_elapsedTime += dt;
    int minutes = static_cast<int>(m_elapsedTime) / 60;
    int seconds = static_cast<int>(m_elapsedTime) % 60;
    int millis = static_cast<int>((m_elapsedTime - (static_cast<float>(seconds) + minutes * 60)) * 100.f);
    m_timeText.setString(std::to_string(minutes) + ':' + (seconds < 10 ? "0" : "")
                         + std::to_string(seconds) + ':' + (millis < 10 ? "0" : "") + std::to_string(millis));
}
