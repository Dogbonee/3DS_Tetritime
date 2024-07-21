//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <Dualie/Graphics.hpp>
#include "Piece.h"

enum PieceType : int;

class System
{
public:
    static constexpr int WIDTH = 400;
    static constexpr int HEIGHT = 240;
    static constexpr int BOARD_WIDTH = 12;
    static constexpr int BOARD_HEIGHT = 21;
    static constexpr float PIECE_SIZE = 10;
    static constexpr int X_MIDDLE = WIDTH / 2 + 5;
    static constexpr int X_OFFSET = X_MIDDLE - PIECE_SIZE * 6 - PIECE_SIZE / 2;
    static constexpr int Y_OFFSET = 25;

    static constexpr float LevelOneTick = 1.f;
    static constexpr float LevelTwoTick = 0.75f;
    static constexpr float LevelThreeTick = 0.5f;
    static constexpr float LevelFourTick = 0.3f;
    static constexpr float LevelFiveTick = 0.15f;
    static constexpr float LevelSixTick = 0.05f;


    static dl::Color ColorPiece(PieceType type);

};

static dl::TextBuffer TStaticBuffer{4096};
static dl::TextBuffer TDynamicBuffer{4096};


#endif //SYSTEM_H
