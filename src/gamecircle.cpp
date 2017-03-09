#include "gamecircle.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

gameCircle::gameCircle()
{
	circle = gameCircle::setCircle(1);
}
gameCircle::gameCircle(float cx,float cy,float radius)
{
    centerx = cx + radius ;
    centery = cy + radius;
    radius = radius;
    circle = gameCircle::setCircle(radius);
    circle.move(cx,cy);

    //std::cout<<"centery is "<<centery <<"\n";
}

float gameCircle::getRadius()
{
    return radius;
}

float gameCircle::getcenterx()
{
    return circle.getGlobalBounds().left + 20;
}

float gameCircle::getcentery()
{
    return circle.getGlobalBounds().top - 20;
}

sf::CircleShape gameCircle::getCircle()
{
    return circle;
}

sf::CircleShape gameCircle::setCircle(float radius)
{
    sf::CircleShape c(radius);
    c.setFillColor(sf::Color::Green);
    return c;
}

void gameCircle::moveball(float velocity,int direction)
{

            float move_x = velocity * cos((float)direction * 3.1416 / 180);
            float move_y = velocity * sin((float)direction * 3.1416 / 180);
            centerx += move_x;
            centery -= move_y;
            //std::cout<<"movex = "<<move_x << "   move y:= "<<move_y<<std::endl;
            circle.move(move_x,-move_y);

}

void gameCircle::reset()
{
    circle.setPosition(280,280);
    centerx = 280 + radius;
    centery = 280 + radius;
}

gameCircle::~gameCircle()
{
    //dtor
}
