#ifndef GAMEPOWERUP_H
#define GAMEPOWERUP_H
#include "gamecircle.h"
#include "pingRectangle.h"
#include <SFML/Graphics.hpp>

class Powerup
{
public:
	Powerup();
	void setpowerup();
	void setpowerupfree();
	bool is_powerup_on();
	void end_duration();
	void take_effect(int);
	bool is_p1_affected();
	bool is_p2_affected();
	bool is_effect_on();
	gameCircle getpowerup();
protected:
	bool disp;
	bool paddle1;
	bool paddle2;
	gameCircle powerup;
};
class Obstacle
{
public:
	int count;
    Obstacle(int);
    bool _gameObstacle();
    void setPowerup();
    sf::RectangleShape getObstacle();
    sf::RectangleShape setObstacle();
    void setobstaclefree();
private:
    bool _isObstacle;
    sf::RectangleShape obstacle;
};

#endif // GAMEPOWERUP_H

