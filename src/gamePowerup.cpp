#include "gamePowerup.h"
#include "pingRectangle.h"
#include "gamecircle.h"

void Obstacle::setPowerup()
{
    int x = rand()%6;
    _isObstacle = true;
}

Obstacle::Obstacle(int i)
{
    _isObstacle = false ;
	count = i;
}

void Obstacle::setobstaclefree()
{
    _isObstacle = false ;
	obstacle.setPosition(0, 0);
}

bool Obstacle::_gameObstacle()
{
    return _isObstacle;
}

sf::RectangleShape Obstacle::setObstacle()
{
	float rect_x, rect_y;
	if (count == 1)
	{
		rect_x = rand() % 180 + 100;
		rect_y = rand() % 550;
	}
	else if (count == 2)
	{
		rect_x = rand() % 180 + 320;
		rect_y = rand() % 550;
	}
    sf::RectangleShape obst(sf::Vector2f(20,50));
    obst.setPosition(rect_x,rect_y);
	_isObstacle = true;
    obstacle = obst;
    return obst;
}

sf::RectangleShape Obstacle::getObstacle()
{
    return obstacle;
}
Powerup::Powerup()
{
	paddle1 = paddle2 = false;
	disp = false;
}
bool Powerup::is_p1_affected()
{
	return paddle1;
}
bool Powerup::is_p2_affected()
{
	return paddle2;
}
void Powerup::setpowerup()
{
	float x = rand() % 360 + 100;
	float y = rand() % 550;
	powerup = gameCircle(x, y, 10);
	disp = true;
}
gameCircle Powerup::getpowerup()
{
	return powerup;
}
void Powerup::setpowerupfree()
{
	disp = false;
}
bool Powerup::is_powerup_on()
{
	return disp;
}
void Powerup::take_effect(int i)
{
	if (i == 1) paddle1 = true;
	else paddle2 = true;
}
void Powerup::end_duration()
{
	paddle1 = paddle2 = false;
}
bool Powerup::is_effect_on()
{
	return paddle1 || paddle2;
}