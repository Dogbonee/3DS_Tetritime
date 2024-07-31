//
// Created by 24crickenbach on 3/26/2024.
//

#include "Button.h"


Button::Button(dl::Vector2f size, std::string text) : callback(nullptr), m_buttonText(TStaticBuffer)
{
    m_buttonShape.setSize(size);
    m_buttonShape.setFillColor(dl::Color(180, 180, 180));
    m_buttonShape.setOutlineThickness(3);
    m_buttonShape.setOrigin(size.x / 2, size.y / 2);

    m_buttonText.setString(text);
    m_buttonText.setScale(dl::Vector2f(0.5, 0.5));
}


void Button::setColor(dl::Color color)
{
    m_buttonShape.setOutlineColor(color);
    m_buttonColor = color;
}

void Button::setPosition(const dl::Vector2f &position)
{
    m_buttonShape.setPosition(position);
    m_buttonText.setPosition(position.x, position.y - 5);
}

void Button::setPosition(float x, float y)
{
    setPosition(dl::Vector2f(x, y));
}

void Button::ButtonUpdate()
{
    static bool hasTouched = false;
    static bool hasReleased = true;
    if (dl::Input::TouchPosition != dl::Vector2f(0, 0))
    {
        hasTouched = true;
    }
    if (dl::Input::TouchPosition != dl::Input::LastTouchPosition)
    {
        hasReleased = true;
    }
    if (hasTouched && hasReleased && dl::Input::TouchPosition == dl::Input::LastTouchPosition &&
        m_buttonShape.getGlobalBounds().contains(dl::Vector2f(dl::Input::LastTouchPosition)) && callback !=
                                                                                                nullptr)
    {
        hasReleased = false;
        callback();
    }
}


void Button::draw(const dl::Vector2f &viewOffset)
{
    m_buttonShape.draw(viewOffset);
    m_buttonText.draw(viewOffset);
}
