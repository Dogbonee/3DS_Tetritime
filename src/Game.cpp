//
// Created by 24crickenbach on 3/20/2024.
//

#include "Game.h"

#include "StateMachine.h"


Game::Game(StateMachine &sm, dl::RenderWindow &window) : State(sm, window),
                                                         m_defaultTickLength(System::LevelOneTick),
                                                         m_tickLength(m_defaultTickLength),
                                                         m_speedTickLength(m_defaultTickLength / 10),
                                                         m_board(&m_currentPiece),
                                                         m_ghostBoard(&m_ghostPiece), m_currentPiece(O_BLOCK),
                                                         m_nextPiece(O_BLOCK),
                                                         m_holdPiece(O_BLOCK),
                                                         m_ghostPiece(m_currentPiece),
                                                         m_currentType(O_BLOCK), m_nextPiecePosition(330, 150),
                                                         m_holdPiecePosition(220, 120), m_hasHeld(false),
                                                         m_hasHeldThisTurn(false), m_isGameOver(false),
                                                         m_clearedLineCount(0),
                                                         m_score(0), m_scoreText(TStaticBuffer),
                                                         m_scoreLabel(TStaticBuffer),
                                                         m_nextLabel(TStaticBuffer), m_holdLabel(TStaticBuffer),
                                                         m_menuButton(dl::Vector2f(80, 50), "Menu")
{


    m_scoreLabel.setPosition(70, 100);
    m_scoreLabel.setString("Score");

    m_nextLabel.setPosition(330, 100);
    m_nextLabel.setString("Next");

    m_holdLabel.setPosition(220, 60);
    m_holdLabel.setString("Hold");


    m_menuButton.setPosition(60, 190);
    m_menuButton.setColor(dl::Color::Red);
    m_menuButton.callback = [this]()
    {
        p_stateMachine->ResetGame();
        p_stateMachine->SwitchState(MENU);
    };


    setScore();

    //Init all ui before this point, because now we're running game functions
    std::srand(std::time(nullptr));
    SpawnPiece(static_cast<PieceType>(std::rand() % 7));
    m_ghostPiece = m_currentPiece;
    HandleNextPiece();
    ManageGhostPiece();

    m_board.setDepth(-5);

}

void Game::Render()
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


void Game::HandleButtonInput()
{

    if (dl::Input::isKeyPressed(dl::Input::RIGHT) && !m_board.WillCollide(MOVE_RIGHT))
    {
        MovePieceComponents(MOVE_RIGHT);
    }

    if (dl::Input::isKeyPressed(dl::Input::LEFT) && !m_board.WillCollide((MOVE_LEFT)))
    {
        MovePieceComponents(MOVE_LEFT);
    }
    if (dl::Input::isKeyPressed(static_cast<dl::Input::Key>(dl::Input::R | dl::Input::X)))
    {
        RotatePieceComponents(CLOCKWISE);
    }
    if (dl::Input::isKeyPressed(dl::Input::A))
    {
        DropPiece();
    }
    if ((dl::Input::isKeyPressed(dl::Input::Y) || dl::Input::isKeyPressed(dl::Input::L)) && !m_hasHeldThisTurn)
    {
        HoldPiece();
    }

}

void Game::Update(const float &dt)
{
    //should handle in other function in future
    //If the down arrow is pressed, the tick length should be way less
    m_tickLength = dl::Input::isKeyHeld(dl::Input::DOWN) ? m_speedTickLength : m_defaultTickLength;
    HandleButtonInput();
    m_menuButton.ButtonUpdate();
    ManageGameClock(dt);
    Render();
}


void Game::setScore()
{
    //Set scoreText string and reposition it
    m_scoreText.setString(std::to_string(m_score));
    m_scoreText.setPosition(70, 130);
}

//Add a new piece to the array
//Note: This ideally would be handled in TetrisBoard and should be done in the near future.
void Game::SpawnPiece(PieceType type)
{
    Piece piece(type);
    m_currentPiece = piece;
    m_currentType = type;
    m_board.SetCurrentPieceType(type);
    int pieceSize = m_currentPiece.GetPieceArray().size();
    for (int y = 0; y < pieceSize; y++)
    {
        for (int x = 0; x < pieceSize; x++)
        {
            if (m_board[y][5 + x] > 5)
            {
                TriggerGameOver();
            }
            m_board[y][5 + x] = m_currentPiece.GetPieceArray()[y][x] * 2;

        }
    }

}


void Game::ManageGameClock(const float &dt)
{
    static float tickTimeRemaining = m_tickLength;
    tickTimeRemaining -= dt;

    if (tickTimeRemaining <= 0 || tickTimeRemaining > m_tickLength)
    {
        Tick();
        tickTimeRemaining = m_tickLength;

    }
}

//Moves piece down if it can, otherwise set the piece
//Returns whether piece can tick again without colliding
bool Game::Tick()
{
    if (m_isGameOver)
    { return false; }
    //Check collision
    if (!m_board.WillCollide(MOVE_DOWN))
    {
        m_currentPiece.Fall();
        m_board.FallPiece();
        return true;
    }

    m_board.SetPiece();
    HandleScoring();
    SpawnPiece(m_nextPiece.GetType());
    HandleNextPiece();
    ManageGhostPiece();
    m_hasHeldThisTurn = false;

    return false;
}

//Moves the array, visual, and ghost pieces all at once
void Game::MovePieceComponents(MovementOption direction)
{
    m_currentPiece.Move(direction);
    m_board.MovePiece(direction);
    ManageGhostPiece();
}

//Rotates the array, visual, and ghost pieces all at once
void Game::RotatePieceComponents(RotationOption direction)
{
    if (m_currentType == O_BLOCK)
    { return; }
    if (m_board.RotatePiece(direction, m_currentPiece))
    {
        m_currentPiece.SyncVisualWithPiece(System::PIECE_SIZE);
        ManageGhostPiece();
    }
}

//Checks and clear lines, and adds to the score based on how many lines were cleared in the tick.
void Game::HandleScoring()
{
    std::vector<int> completedLines = m_board.CheckLines();
    if (completedLines.size() == 0)
    { return; }
    m_clearedLineCount += completedLines.size();
    int earnedScore = 0;
    switch (completedLines.size())
    {
        case 1:
            earnedScore = 100;
            break;
        case 2:
            earnedScore = 300;
            break;
        case 3:
            earnedScore = 600;
            break;
        case 4:
            earnedScore = 1000;
            break;
    }
    m_score += earnedScore;

    if (m_score > 4000)
    {
        m_defaultTickLength = System::LevelTwoTick;
    }
    if (m_score > 12000)
    {
        m_defaultTickLength = System::LevelThreeTick;
    }
    if (m_score > 24000)
    {
        m_defaultTickLength = System::LevelFourTick;
    }
    if (m_score > 40000)
    {
        m_defaultTickLength = System::LevelFiveTick;
    }
    if (m_score > 60000)
    {
        m_defaultTickLength = System::LevelSixTick;
    }
    //Speed length needs to shorten every time the default tick length is shortened,
    //otherwise pressing the down arrow would eventually be slower than the default speed.
    m_speedTickLength = m_defaultTickLength / 10;
    setScore();
}

//Handles the drop of the ghost piece array and visual
void Game::HandleGhostPiece()
{
    //We can simulate a fallen piece by finding the lowest spot that the current piece can go
    while (!m_ghostBoard.WillCollide(MOVE_DOWN))
    {
        m_ghostPiece.Fall();
        m_ghostBoard.FallPiece();
    }
}

//Makes the ghost piece equal to the current piece and reshades
void Game::ResetGhostPiece()
{
    m_ghostPiece = m_currentPiece;
    m_ghostPiece.MakeTransparent();
}

//Handles all the ghost piece functions: resets the ghostboard to the board,
//resets the ghost piece, and handles the dropping of the ghost piece.
void Game::ManageGhostPiece()
{
    m_ghostBoard = m_board;
    ResetGhostPiece();
    HandleGhostPiece();
}

//Fetches a new random piece and sets its position to the designated next piece position
void Game::HandleNextPiece(PieceType type)
{
    m_nextPiece = {type};
    m_nextPiece.SetPosition(m_nextPiecePosition);
    m_nextPiece.SetPieceSize(20);
    if (m_nextPiece.GetType() == I_BLOCK)
    {
        m_nextPiece.SetPosition(dl::Vector2f(m_nextPiecePosition.x + 30, m_nextPiecePosition.y + 20));
    } else if (m_nextPiece.GetType() == O_BLOCK)
    {
        m_nextPiece.SetPosition(dl::Vector2f(m_nextPiecePosition.x + 10, m_nextPiecePosition.y + 20));
    }
}

//Holds a piece
void Game::HoldPiece()
{

    //clear currentpiece from board
    for (int y = 0; y < 21; y++)
    {
        for (int x = 0; x < 12; x++)
        {
            if (m_board[y][x] == 2)
            {
                m_board[y][x] = 0;

            }
        }
    }

    //Temporary variable
    PieceType currentType = m_currentType;
    //If there is a current hold piece, switch the current piece out for the hold piece.
    //Otherwise, simply hold the current piece and spawn a new piece based on the next piece
    SpawnPiece(m_hasHeld ? m_holdPiece.GetType() : m_nextPiece.GetType());
    m_holdPiece = {currentType};
    m_holdPiece.SetPosition(m_holdPiecePosition);
    if (m_holdPiece.GetType() == I_BLOCK)
    {
        m_holdPiece.SetPosition(dl::Vector2f(m_holdPiecePosition.x + 30, m_holdPiecePosition.y + 20));
    } else if (m_holdPiece.GetType() == O_BLOCK)
    {
        m_holdPiece.SetPosition(dl::Vector2f(m_holdPiecePosition.x + 10, m_holdPiecePosition.y + 15));
    }
    m_holdPiece.SetPieceSize(20);
    m_board.ResetPiece();
    m_ghostBoard.ResetPiece();
    ManageGhostPiece();
    //Prevents default block from showing in the hold piece if the player has not yet held this game
    m_hasHeld = true;
    //Prevents multiple holds during a piece
    m_hasHeldThisTurn = true;
}

//Runs Tick until it returns collision
void Game::DropPiece()
{
    if (m_isGameOver)
    { return; }
    while (Tick())
    {}

}

//Set the bool game over to true and set the final score in the game over screen
void Game::TriggerGameOver()
{

    m_isGameOver = true;
    m_gameOverScreen.SetGameOverScore(m_score);
}

