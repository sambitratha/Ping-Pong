#include "pingRectangle.h"

#include <iostream>
#include <SFML/Graphics.hpp>

pingRectangle::pingRectangle(int px,int py,int width,int height)
{
    posx = px;
    posy = py;
    width = width;
    height = height;
    rect = pingRectangle::createRect(width,height);
    rect.setPosition(posx,posy);
}

pingRectangle::pingRectangle()
{

}

void pingRectangle::scale(float x_scale,float y_scale)
{
    rect.scale(sf::Vector2f(x_scale,y_scale));
    width *= x_scale;
    height *= y_scale;
}

int pingRectangle::getHeight()
{
    return height;
}

int pingRectangle::getWidth()
{
    return width;
}

float pingRectangle::getposx()
{
    return posx;
}

float pingRectangle::getposy()
{
    return posy;
}

sf::RectangleShape pingRectangle::getShape()
{
    return rect;
}

sf::RectangleShape pingRectangle::createRect(float width,float height)
{

    sf::RectangleShape shape(sf::Vector2f(width,height));
    //shape.setFillColor(sf::Color::Magenta);
    return shape;
}

void pingRectangle::movePad(float x,float y)
{
    rect.move(x,y);
    posx += x ;
    posy += y;
}

pingRectangle::pingRectangle(int px,int py,int width,int height,int color)
{

    sf::RectangleShape shape(sf::Vector2f(width,height));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(px,py);
    rect = shape;
}

