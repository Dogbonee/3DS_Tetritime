//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef APP_H
#define APP_H


#include "Piece.h"
#include "System.h"
#include "TetrisBoard.h"
#include "GameOver.h"
#include "State.h"
#include <ctime>
#include <cmath>
#include <iostream>

#include "Button.h"

class Game : public State
{


protected:
    void Render() override;

    void HandleButtonInput() override;
    void Update(const float &dt) override;

    float m_defaultTickLength;
    float m_tickLength;
    float m_speedTickLength;

    GameOver m_gameOverScreen;


public:
    Game(StateMachine &sm, dl::RenderWindow &window);


protected:
    //Game objects
    TetrisBoard m_board;
    TetrisBoard m_ghostBoard;

    Piece m_currentPiece;
    Piece m_nextPiece;
    Piece m_holdPiece;
    Piece m_ghostPiece;
    PieceType m_currentType;

    dl::Vector2f m_nextPiecePosition;
    dl::Vector2f m_holdPiecePosition;

    bool m_hasHeld;
    bool m_hasHeldThisTurn;

    bool m_isGameOver;

    unsigned int m_clearedLineCount;
    unsigned long m_score;

    //UI
    dl::Text m_scoreText;
    dl::Text m_scoreLabel;
    dl::Text m_nextLabel;
    dl::Text m_holdLabel;


    Button m_menuButton;

    void setScore();

    //Game functions
    void SpawnPiece(PieceType type);

    virtual void ManageGameClock(const float &dt);
    virtual bool Tick();
    virtual void HandleScoring();
    void MovePieceComponents(MovementOption direction);
    void RotatePieceComponents(RotationOption direction);
    void HandleGhostPiece();
    void ResetGhostPiece();
    void ManageGhostPiece();
    void HandleNextPiece(PieceType type = static_cast<PieceType>(std::rand() % 7));
    void HoldPiece();
    virtual void DropPiece();
    void TriggerGameOver();
};


#endif //APP_H
