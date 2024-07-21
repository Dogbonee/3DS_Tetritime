//
// Created by 24crickenbach on 3/20/2024.
//

#include "Piece.h"

#include <cmath>
#include <iostream>


Piece::Piece(PieceType type) : m_level(0)
{
    m_type = type;

    generatePieceArray(type);
    SyncVisualWithPiece(System::PIECE_SIZE);


}


void Piece::generatePieceArray(int type)
{
    switch (type)
    {
        case O_BLOCK:
            m_piece = {{1, 1, 0},
                       {1, 1, 0},
                       {0, 0, 0}};
            break;
        case I_BLOCK:
            m_piece = {
                    {1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 0, 0, 0}};
            break;
        case S_BLOCK:
            m_piece = {
                    {0, 0, 0},
                    {0, 1, 1},
                    {1, 1, 0}};
            break;
        case Z_BLOCK:
            m_piece = {
                    {0, 0, 0},
                    {1, 1, 0},
                    {0, 1, 1}};
            break;
        case L_BLOCK:
            m_piece = {
                    {0, 0, 0},
                    {1, 0, 0},
                    {1, 1, 1}};
            break;
        case J_BLOCK:
            m_piece = {
                    {0, 0, 0},
                    {0, 0, 1},
                    {1, 1, 1}};
            break;
        case T_BLOCK:
            m_piece = {
                    {0, 0, 0},
                    {0, 1, 0},
                    {1, 1, 1}};
            break;

        default:
            std::cout << "Illegal piece type specified\n";
            exit(1);
    }

}


void Piece::Move(MovementOption direction)
{
    for (auto &piece: m_pieceVisual)
    {
        piece.move(System::PIECE_SIZE * direction, 0);
    }
}

//Moves the piece visual and level variable down by one
void Piece::Fall()
{
    m_level++;
    for (auto &piece: m_pieceVisual)
    {
        piece.move(0, System::PIECE_SIZE);
    }
}

//Makes the piece slightly see through (for ghost piece)
void Piece::MakeTransparent()
{
    auto transparentColor = m_pieceVisual[0].getFillColor().getColorValue();
    transparentColor = (transparentColor & 0x00FFFFFF) | (0x9B << 24);
    for (auto &piece: m_pieceVisual)
    {
        piece.setFillColor(dl::Color(transparentColor));
    }
}

PieceType Piece::GetType()
{
    return m_type;
}


const PieceArray &Piece::GetPieceArray() const
{
    return m_piece;
}


dl::Vector2f Piece::GetPosition() const
{
    return m_pieceVisual[0].getPosition();
}

void Piece::SetPosition(const dl::Vector2f &position)
{
    for (auto &rect: m_pieceVisual)
    {
        rect.setPosition(position);
    }
}


void Piece::draw(const dl::Vector2f &viewOffset) const
{
    for (auto &rect: m_pieceVisual)
    {
        rect.draw(viewOffset);
    }
}

void Piece::SetPieceArray(PieceArray array)
{
    m_piece = array;
}

void Piece::SetPieceSize(float size)
{
    SyncVisualWithPiece(size);
}

void Piece::SyncVisualWithPiece(float size)
{
    bool isSpawning = m_pieceVisual.empty();
    dl::Vector2f position;
    if (isSpawning)
    {
        position = dl::Vector2f(System::X_MIDDLE, System::Y_OFFSET);
    } else
    {
        position = m_pieceVisual[0].getPosition();
    }

    m_pieceVisual.clear();
    for (int y = 0; y < m_piece.size(); y++)
    {
        for (int x = 0; x < m_piece[0].size(); x++)
        {
            if (m_piece[y][x])
            {
                dl::RectangleShape rect(dl::Vector2f(size, size));
                //Since the origin is different for every piece, the position needs to be changed depending on the x/y values
                //Every rect origin should be in the same point (the center of the piece visual)
                rect.setPosition(position);
                if (m_type != I_BLOCK)
                {
                    rect.setOrigin(size * (1 - x) + (size / 2), size * (1 - y) + size / 2);
                } else
                {
                    rect.setOrigin(size * (2 - x), (2 - y) * size);
                }
                if(m_piece.size() == 4 && isSpawning){rect.move(System::PIECE_SIZE/2, System::PIECE_SIZE/2);}
                rect.setOutlineColor(dl::Color::Black);
                rect.setOutlineThickness(1);
                rect.setFillColor(System::ColorPiece(m_type));
                m_pieceVisual.push_back(rect);
            }
        }
    }
}
