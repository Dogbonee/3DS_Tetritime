//
// Created by 24crickenbach on 3/20/2024.
//

#include "TetrisBoard.h"

#include <iostream>


TetrisBoard::TetrisBoard(Piece* pCurrentPiece) : m_piecePos(5, 0), p_currentPiece(pCurrentPiece)
{
    m_frame.setSize(dl::Vector2f(120, 200));
    m_frame.setFillColor(dl::Color(180, 180, 180));
    m_frame.setOutlineColor(dl::Color::Red);
    m_frame.setOutlineThickness(10);
    m_frame.setOrigin(dl::Vector2f(m_frame.getSize().x / 2, m_frame.getSize().y / 2));
    m_frame.setPosition(System::WIDTH / 2, System::HEIGHT / 2);

    //Might be able to clean this up with a for loop but I'm too lazy to worry about
    //that right now. Maybe a kind soul will come in clutch with a PR :D
    m_board = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };


}


//Rotates current piece (array only)
bool TetrisBoard::RotatePiece(RotationOption rotation, Piece &currentPiece)
{
    //TODO: change rotation algorithm to one with O(1) extra space

    //Rotating the O_BLOCK feels wrong, so don't do it
    if (m_currentType == O_BLOCK)
    { return false; }

    //Get size of piece array
    int n = 3 + (m_currentType == I_BLOCK);

    //create arrays to store original and rotated versions of the pieces
    int arr[4][4];
    int rotatedArr[4][4];

    //Hack to avoid sigsegv when rotating i piece at border
    //Maybe unneccessary at this point but I don't want to test
    if (m_currentType == I_BLOCK && m_piecePos.x > 7)
    { return false; }
    for (int i = m_piecePos.y; i < m_piecePos.y + n; i++)
    {
        for (int j = m_piecePos.x; j < m_piecePos.x + n; j++)
        {
            //Try to populate array with m_board
            arr[i - m_piecePos.y][j - m_piecePos.x] = (m_board[i][j] != 1 && m_board[i][j] < 6) ? m_board[i][j] : 0;
        }
    }

    //Rotate array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rotatedArr[n - 1 - i][j] = arr[n - 1 - j][n - 1 - i];
        }
    }

    //Check for collision; for every part of piece (2) in rotated array, check if
    //the board at that spot is filled. If it is, return false.
    for (int i = m_piecePos.y; i < m_piecePos.y + n; i++)
    {
        for (int j = m_piecePos.x; j < m_piecePos.x + n; j++)
        {
            if (rotatedArr[i - m_piecePos.y][j - m_piecePos.x] == 2 && (m_board[i][j] == 1 || m_board[i][j] > 5))
            {
                return false;
            }
        }
    }

    //At this point we know the piece is good to rotate, so insert the rotated array
    //into the board (only the filled parts of the array)
    for (int i = m_piecePos.y; i < m_piecePos.y + n; i++)
    {
        for (int j = m_piecePos.x; j < m_piecePos.x + n; j++)
        {
            m_board[i][j] = (m_board[i][j] == 1 || m_board[i][j] > 5) ? m_board[i][j] : rotatedArr[i - m_piecePos.y][j -
                                                                                                                     m_piecePos.x];
        }

    }

    PieceArray pieceArr;
    for (int i = 0; i < n; i++)
    {
        pieceArr.emplace_back();
        for (int j = 0; j < n; j++)
        {
            pieceArr[i].emplace_back(rotatedArr[i][j]);
        }
    }
    currentPiece.SetPieceArray(pieceArr);
    return true;
}

//Drops the current piece one block down
void TetrisBoard::FallPiece()
{
    for (int y = 0; y < m_board.size(); y++)
    {
        for (int x = 0; x < m_board[0].size(); x++)
        {
            //if board is not the piece, return
            if (m_board[y][x] < 2)
            { continue; }
            //if board is the piece and has not been affected (2), move the piece num down in the board and set it as affected (3)
            if (m_board[y][x] == 2)
            {
                m_board[y + 1][x] += 3;
                m_board[y][x] = 0;
            }
            //if board is the piece and has been affected (3), set it to not affected (2) and continue.
            //This prevents an infinite loop of m_board[y+1][x] always being moved down
            if (m_board[y][x] == 3)
            {
                m_board[y][x] = 2;
            }
            //if board is the piece and has been affected and needs to move down again, increment the next one down
            //and set it equal to not affected. This occurs when a piecenum that needs to move down moves onto another piecenum
            if (m_board[y][x] == 5)
            {
                m_board[y + 1][x] += 3;
                m_board[y][x] = 2;
            }
        }
    }
    m_piecePos.y++;
}

//Moves the current piece in the specified direction
void TetrisBoard::MovePiece(MovementOption direction)
{
    for (int y = 0; y < m_board.size(); y++)
    {
        //The for loop has to run in the direction the piece is moving, otherwise affected piecenums (3) will not be set to two.
        //This abonination of a for loop sets the directon of the for loop to run right->left if the direction is left,
        //otherwise run left->right
        for (int x = (m_board[0].size() - 1) * (direction == MOVE_LEFT);
             x != (m_board[0].size() - 1) * (direction == MOVE_RIGHT); x += direction)
        {
            //if board is not the piece, return
            if (m_board[y][x] < 2)
            { continue; }
            //if board is the piece and has not been affected (2), move the piece num over in the board and set it as affected (3)
            if (m_board[y][x] == 2)
            {
                m_board[y][x + direction] += 3;
                m_board[y][x] = 0;
            }
            //if board is the piece and has been affected (3), set it to not affected (2) and continue.
            //This prevents an infinite loop of m_board[y][x + dir] always being moved over
            if (m_board[y][x] == 3)
            {
                m_board[y][x] = 2;
            }
            //if board is the piece and has been affected and needs to move down again, increment the next one over
            //and set it equal to not affected. This occurs when a piecenum that needs to move over moves onto another piecenum
            if (m_board[y][x] == 5)
            {
                m_board[y][x + direction] += 3;
                m_board[y][x] = 2;
            }

        }
    }
    m_piecePos.x += direction;
}

//Check if moving the piece in the given direction will cause a collision
//Returns true if moving the piece will cause a collision
bool TetrisBoard::WillCollide(MovementOption direction)
{
    uint8_t movingDown = direction == 0;
    std::vector<dl::Vector2i> pieceCoords;
    for (int y = 0; y < m_board.size(); y++)
    {
        for (int x = 0; x < m_board[0].size(); x++)
        {
            if (m_board[y][x] == 2)
            {
                pieceCoords.emplace_back(x, y);
            }
        }
    }
    for (auto &coord: pieceCoords)
    {
        if (m_board[coord.y + movingDown][coord.x + direction] == 1 ||
            m_board[coord.y + movingDown][coord.x + direction] > 5)
        {
            return true;
        }
    }

    return false;
}

//Completes the current piece's journey and makes it part of the board.
void TetrisBoard::SetPiece()
{
    std::vector<dl::Vector2i> pieceCoords;
    for (int y = 0; y < m_board.size(); y++)
    {
        for (int x = 0; x < m_board[0].size(); x++)
        {
            if (m_board[y][x] == 2)
            {
                //We increment by six because movement uses ints up to 5
                m_board[y][x] = p_currentPiece->GetType() + 6;

                AddRect(p_currentPiece->GetType(), dl::Vector2i(x, y));


            }
        }
    }
    ResetPiece();
}

//Adds a visual rect (Not a piece) at the given position in board coordinates.
void TetrisBoard::AddRect(PieceType type, dl::Vector2i pos)
{
    dl::RectangleShape rect(dl::Vector2f(System::PIECE_SIZE, System::PIECE_SIZE));
    rect.setPosition(System::PIECE_SIZE * pos.x + System::X_OFFSET,
                     System::PIECE_SIZE * (pos.y - 1) + System::Y_OFFSET - System::PIECE_SIZE / 2);
    rect.setOutlineColor(dl::Color::Black);
    rect.setOutlineThickness(1);
    rect.setFillColor(System::ColorPiece(type));
    m_vRect.push_back(rect);
}

//Sets the current piece position to the starting position
void TetrisBoard::ResetPiece()
{
    m_piecePos = dl::Vector2i(5, 0);
}

//Scans the board and looks for completed lines.
//Returns a vector of y positions in board coordinates of all the completed lines found.
std::vector<int> TetrisBoard::CheckLines()
{
    std::vector<int> completedLines;
    for (int y = 0; y < m_board.size() - 1; y++)
    {
        bool lineComplete = true;
        for (int x = 1; x < m_board[0].size() - 1; x++)
        {
            if (m_board[y][x] != 1 && m_board[y][x] < 6)
            {
                lineComplete = false;
            }
        }
        if (lineComplete)
        {
            completedLines.push_back(y);
        }
    }
    for (const auto line: completedLines)
    {
        ClearLine(line);
    }
    return completedLines;
}

//Clear a line at the specified board position and shift everything upwards down
void TetrisBoard::ClearLine(const int line)
{
    //Possible bug in the future
    std::vector<int> emptyLine = m_board[0];

    //Rather than modifying the array in place, its easier to just trashcan the entire
    //line and add a new line at the beginning of m_board. The other lines are automatically
    //moved down for us by the erase function (yay)
    m_board.erase(m_board.begin() + line);
    m_board.insert(m_board.begin(), emptyLine);


    //Clear all visual rects in the line
    for (int i = 0; i < m_vRect.size(); i++)
    {
        if (m_vRect[i].getPosition().y == (line - 1) * System::PIECE_SIZE + System::Y_OFFSET - System::PIECE_SIZE / 2)
        {
            m_vRect.erase(m_vRect.begin() + i);
            i--;
        }
    }
    //Move visual rects down
    for (auto &rect: m_vRect)
    {
        if (rect.getPosition().y < (line - 1) * System::PIECE_SIZE + System::Y_OFFSET - System::PIECE_SIZE / 2)
        {
            rect.move(0, System::PIECE_SIZE);
        }
    }

}



const Board &TetrisBoard::GetBoard() const
{
    return m_board;
}

void TetrisBoard::SetCurrentPieceType(PieceType type)
{
    m_currentType = type;
}

std::vector<int> &TetrisBoard::operator[](size_t index)
{
    return m_board[index];
}

TetrisBoard &TetrisBoard::operator=(TetrisBoard board)
{
    m_board = board.GetBoard();
    return *this;
}

void TetrisBoard::draw(const dl::Vector2f &viewOffset)
{
    m_frame.draw(viewOffset);
    for (auto &i: m_vRect)
    {
        i.draw(viewOffset);
    }
}


