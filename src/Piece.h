//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef PIECE_H
#define PIECE_H

#include "System.h"
#include <vector>


using std::vector;

enum RotationOption : int;
enum MovementOption : int;

enum PieceType : int
{

    O_BLOCK = 0,
    I_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    L_BLOCK,
    J_BLOCK,
    T_BLOCK

};


typedef vector<vector<uint8_t>> PieceArray;

class Piece : public dl::Drawable
{

    PieceArray m_piece;
    vector<dl::RectangleShape> m_pieceVisual;
    PieceType m_type;
    int m_level;

    void generatePieceArray(int type);


public:

    Piece(PieceType type);

    void SetPieceArray(PieceArray array);
    void SetPieceSize(float size);

    void SyncVisualWithPiece(float size);

    void Move(MovementOption direction);
    void Fall();
    void MakeTransparent();

    PieceType GetType();
    const PieceArray &GetPieceArray() const;
    dl::Vector2f GetPosition() const;
    void SetPosition(const dl::Vector2f &position);
    void draw(const dl::Vector2f &viewOffset) override;
};


#endif //PIECE_H
