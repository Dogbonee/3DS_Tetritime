//
// Created by minri on 3/24/2024.
//
#include "System.h"

#include <iostream>


dl::Color System::ColorPiece(PieceType type)
{
    switch (type)
    {
        case O_BLOCK:
            return dl::Color::Yellow;
        case I_BLOCK:
            return {48, 213, 200};
        case S_BLOCK:
            return dl::Color::Red;
        case Z_BLOCK:
            return dl::Color::Green;
        case L_BLOCK:
            //Orange
            return {255, 165, 0};
        case J_BLOCK:
            //Pink
            return {255, 105, 180};
        case T_BLOCK:
            return {128, 0, 128};
    }
    //Should never be here
    std::cout << "Warning: Color piece type out of range\n";
    return dl::Color::White;
}

