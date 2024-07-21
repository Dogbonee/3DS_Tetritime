//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "System.h"

class Button : public dl::Drawable
{


    dl::RectangleShape m_buttonShape;
    dl::Text m_buttonText;
    dl::Color m_buttonColor;

public:
    Button(dl::Vector2f size, std::string text);


    void setColor(dl::Color color);
    void setPosition(const dl::Vector2f &position);
    void setPosition(float x, float y);
    void ButtonUpdate();

    void draw(const dl::Vector2f &viewOffset) const override;

    std::function<void()> callback;

};


#endif //BUTTON_H
