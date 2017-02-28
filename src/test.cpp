#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "pingRectangle.h"
#include "gamecircle.h"
#include <math.h>
#define player1posx 20
#define player2posx 760
#define radius 20
#include "gamePowerup.h"
#define rect_width 30
#define windowlength 800
#define windowheight 600
#include <sstream>
#include "gamestart.h"
#define max_Score 10
#include "gameend.h"
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>


/************ FUNCTION DECLARATIONS ******************/

void controlpad1();
void controlpad2();
void display();
void draw_shape(sf::RenderWindow&);
int _getDirection();
void powerthread();

/*****************************************************/

/************************* global variables ************************/

bool up = false, down = false, player2up = false, player2down = false, ball_controller;
bool P1moveup = false, P2moveup = false, P1movedown = false, P2movedown = false ;
bool _end = false;
float velocity = 2 ;
float rectLength = 150;
bool speed_brag = false;
int score_left = 0;
int score_right = 0;
int countdown;
sf::Font font;
sf::Mutex mutex;
sf::Text countdownText;
sf::Music music;
std::string player1_Name = "Madara uchiha", player2_Name = "Hashirama Senju";

gameCircle cBall(100,100,20);
gameCircle fake_ball;
pingRectangle barrier;
sf::CircleShape circle = cBall.getCircle();
pingRectangle player1(player1posx,150, rect_width,rectLength);
pingRectangle player2(player2posx,150, rect_width,rectLength);
Obstacle Powerup1(1);
Obstacle Powerup2(2);
Powerup power_invis;
Powerup power_diminish;
Powerup illusion;
Powerup restriction;
int direction = 45;
std::string convert(int a)
{
	std::ostringstream ss;
	ss << a;
	return ss.str();
}
/******************************************************************/



/*********************** MAIN FUNCTION ********************/

int main()
{
    //srand(time(NULL));
    sf::RenderWindow win(sf::VideoMode(windowlength, windowheight), "SFML Test");
    win.setActive(false);
    gameStart s("Ping Pong Game","New Game","Set PlayerName",&win);
    if(s.getPLayer1() != "")player1_Name = s.getPLayer1();
    if(s.getPLayer2() != "")player2_Name = s.getPLayer2();
    sf::Thread t(&display);
    sf::Thread pad1(&controlpad1);
    sf::Thread pad2(&controlpad2);
	sf::Thread obstac(&powerthread);
	if (!font.loadFromFile("3Dumb.ttf"))
	{

	}
	t.launch();
	pad1.launch();
	pad2.launch();
	obstac.launch();

	if (!music.openFromFile("narutotheme.ogg"))
	{
		std::cout << "error\n";
	}
	music.play();
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                down = true;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                up = true;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player2up = true;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player2down = true;
        }

        if(score_left == max_Score || score_right == max_Score)
            _end = true;

        win.clear();
		if (!_end)draw_shape(win);
		else
        {
            music.stop();
            gameend e(score_left, score_right, player1_Name, player2_Name, &win);
        }
		win.display();
    }
    return 0;
}


/*************************END MAIN *******************/

void powerthread()
{
	int s = 0, k = 0,l=0;
	int illusion_time = 0;
	int restriction_time = 0 ;
	for (int i = 0; true; i++)
	{
	/*	if (s > 0)
		{
			s--;
			if (s == 0) power_invis.end_duration();
		}
		if (l > 0)
		{
			l--;
			if (l == 0)
			{
				if (power_diminish.is_p1_affected()) player1.scale(1.0, 2.0);
				else player2.scale(1.0, 2.0);
				power_diminish.end_duration();

			}
		}
		if (k > 0)
		{
			k--;
			if(countdown) countdown--;
			if (k == 10)
			{
				speed_brag = false;
				velocity = 4;
			}
			if (k == 0) velocity = 2;
		}
		*/

		if ( restriction_time > 0)
        {
            restriction_time -- ;
            if (restriction_time == 0)
                restriction.end_duration();

        }

		if (i % 60 == 0)
		{
			Powerup1.setObstacle();
		}
		if (i % 60 == 3)
		{
			Powerup1.setobstaclefree();
		}
		if (i % 60 == 1)
		{
			Powerup2.setObstacle();
		}
		if (i % 60 == 4)
		{
			Powerup2.setobstaclefree();
		}

		if ( (restriction.is_p1_affected() || restriction.is_p2_affected() ) && restriction_time == 0 )
            restriction_time = 15;

		/*
		if (i % 60 == 41)
		{
			power_invis.setpowerup();
		}
		else if (power_invis.is_powerup_on() && i % 60 == 50)
		{
			power_invis.setpowerupfree();
		}
		if((power_invis.is_p1_affected() ||power_invis.is_p2_affected()) && s==0)
		{
			s = 5;
		}
		if (i % 60 == 21)
		{
			speed_brag = true;
			k = 15;
			countdown = 5;
		}
		if (i % 60 == 30)
		{
			power_diminish.setpowerup();
		}
		else if (power_diminish.is_powerup_on() && i % 60 == 40)
		{
			power_diminish.setpowerupfree();
		}
		if ((power_diminish.is_p1_affected() || power_diminish.is_p2_affected()) && l == 0)
		{
			l = 10;
		}
		*/
		if (i % 60 == 5)
		{
			restriction.setpowerup();
		}
		else if (restriction.is_powerup_on() && i % 60 == 55)
		{
			restriction.setpowerupfree();
		}
		Sleep(1000);
	}
}
void  draw_shape(sf::RenderWindow& window)
{
    if (Powerup1._gameObstacle())window.draw(Powerup1.getObstacle());
	if (power_invis.is_powerup_on()) window.draw(power_invis.getpowerup().getCircle());
	if (power_diminish.is_powerup_on()) window.draw(power_diminish.getpowerup().getCircle());
    if (!power_invis.is_p2_affected())window.draw(player2.getShape());
	if (!power_invis.is_p1_affected()) window.draw(player1.getShape());
    window.draw(cBall.getCircle());
	if (Powerup2._gameObstacle()) window.draw(Powerup2.getObstacle());
	if (illusion.is_powerup_on()) window.draw(illusion.getpowerup().getCircle());
	if (illusion.is_effect_on())
		window.draw(fake_ball.getCircle());
	if(speed_brag)
	{
		countdownText.setFont(font);
		countdownText.setString("be ready\n    " + convert(countdown));
		countdownText.setFillColor(sf::Color::Magenta);
		countdownText.setCharacterSize(30);
		countdownText.setPosition(200, 100);
		window.draw(countdownText);
	}
    if (restriction.is_powerup_on()) window.draw(restriction.getpowerup().getCircle());

	if (restriction.is_effect_on() || restriction.is_p2_affected() || restriction.is_p1_affected())
        window.draw(barrier.getShape());
}

void display()
{
    while(1)
    {
        direction = _getDirection();
        cBall.moveball(velocity,direction);
		if (illusion.is_effect_on())
			fake_ball.moveball(velocity, fake_ball.diren);
		sf::sleep(sf::milliseconds(8));
    }
}

void controlpad1()
{
    while(1)
    {
        if( up)
        {
            if(restriction.is_p1_affected() && player1.getposy() <= barrier.getposy() + 2){}

            else
               player1.movePad(0,-5);
            up = false;
        }

        if (down)
        {
             player1.movePad(0,5);
             down = false;
        }

    }
}

void controlpad2()
{
    while(1)
    {
        if(player2up)
        {

            if(restriction.is_p2_affected() && player2.getposy() <= barrier.getposy() + 2){}
            else
                player2.movePad(0,-5);
            player2up = false;
        }

        if (player2down)
        {
             player2.movePad(0,5);
             player2down = false;
        }
    }
}

int _getDirection()
{

    if (restriction.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(restriction.getpowerup().getCircle().getGlobalBounds()) )
	{
		std::cout << "restriction on\n";
		restriction.setpowerupfree();
		if(ball_controller)
        {
            restriction.take_effect(2);
            float y = player1.getposy() - rand()%((int)player1.getShape().getPosition().y - 10) + 10;
            barrier = pingRectangle(windowlength - 40,y,40,2);
        }
		else
        {
            restriction.take_effect(1);
            float y = player2.getposy() - rand()%((int)player2.getShape().getPosition().y - 10) + 10;
            barrier = pingRectangle(0,y,40,2);

        }

	}

	if (illusion.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(illusion.getpowerup().getCircle().getGlobalBounds()) )
	{
		std::cout << "illusion on\n0";
		illusion.setpowerupfree();
		illusion.take_effect(1);
		fake_ball = gameCircle(cBall.getcenterx(), cBall.getcentery(), 20);
		fake_ball.diren = direction + rand() % 10 +20;
		if (fake_ball.diren > 180) fake_ball.diren -= 360;
		else if (fake_ball.diren < -180) fake_ball.diren += 360;

	}
	if (power_invis.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(power_invis.getpowerup().getCircle().getGlobalBounds()))
	{
		power_invis.setpowerupfree();
		if(ball_controller)power_invis.take_effect(2);
		else power_invis.take_effect(1);

	}
	if (power_diminish.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(power_diminish.getpowerup().getCircle().getGlobalBounds()))
	{
		power_diminish.setpowerupfree();
		if (ball_controller)
		{
			power_diminish.take_effect(2);
			player2.scale(1.0, 0.5);
		}
		else
		{
			power_diminish.take_effect(1);
			player1.scale(1.0, 0.5);
		}

	}
	if (cBall.getCircle().getGlobalBounds().intersects(player1.getShape().getGlobalBounds()))
	{
		ball_controller = true;
		if (direction > 90)
			direction = 180 - direction;

		else if (direction < -90)
			direction = -direction - 180;

		else {}

		if (cBall.getCircle().getPosition().y >= player1.getShape().getPosition().y + ((float)rectLength * 0.9))
			direction -= 10;

		else if (cBall.getCircle().getPosition().y <= player1.getShape().getPosition().y + ((float)rectLength * 0.1))
			direction += 10;

		else {}

		if (P1moveup) direction += 10;
		if (P1movedown) direction -= 10;

		if (direction > 180) direction -= 360;
		else if (direction < -180) direction += 360;

	}

	else if (cBall.getCircle().getGlobalBounds().intersects(player2.getShape().getGlobalBounds()))
	{
		ball_controller = false;
		if (direction < 90 && direction > 0)
			direction = 180 - direction;

		else if (direction > -90 && direction <0)
			direction = -direction - 180;

		else {}

		if (cBall.getCircle().getPosition().y >= player2.getShape().getPosition().y + ((float)rectLength * 0.9))
			direction += 10;

		else if (cBall.getCircle().getPosition().y <= player2.getShape().getPosition().y + ((float)rectLength * 0.1))
			direction -= 10;

		else {}

		if (P1moveup) direction += 10;
		if (P1movedown) direction -= 10;

		if (direction > 180) direction -= 360;
		else if (direction < -180) direction += 360;


	}
	else if (cBall.getCircle().getGlobalBounds().intersects(Powerup1.getObstacle().getGlobalBounds()))
	{
		if (cBall.getcentery() - radius <= Powerup1.getObstacle().getPosition().y + 50 || cBall.getcentery() + radius >= Powerup1.getObstacle().getPosition().y)
		{
			direction *= -1;
		}
		else
		{
			if (direction >= 0) direction = 180 - direction;
			else  direction = -180 - direction;
			if (ball_controller) ball_controller = false;
			else ball_controller = true;
		}

		if (direction > 180) direction -= 360;
		else if (direction < -180) direction += 360;
	}
	else if (cBall.getCircle().getGlobalBounds().intersects(Powerup2.getObstacle().getGlobalBounds()))
	{

		if (cBall.getcentery() - radius <= Powerup2.getObstacle().getPosition().y + 50 || cBall.getcentery() + radius >= Powerup2.getObstacle().getPosition().y)
		{
			direction *= -1;
		}
		else
		{
			if (direction >= 0) direction = 180 - direction;
			else  direction = -180 - direction;
			if (ball_controller) ball_controller = false;
			else ball_controller = true;
		}

		if (direction > 180) direction -= 360;
		else if (direction < -180) direction += 360;
	}
	else if ((cBall.getcentery() >= 570 && direction < 0) || (cBall.getcentery() <= 30 && direction > 0))
	{
		direction *= -1;
	}

	else if (cBall.getcenterx() <= player1posx + (rect_width * 0.7) || cBall.getcenterx() >= player2posx - (rect_width * 0.3))
	{
	    if(cBall.getcenterx() <= player1posx + (rect_width * 0.7))
            score_right ++;
        else
            score_left ++;

		cBall.reset();
		Sleep(2000);
		direction = rand() % 40 + 10;
		ball_controller = true;
		int i = rand() % 4;
		if (i==0) direction *= -1;
		else if (i == 1)
		{
			direction += 90;
			ball_controller = false;
		}
		else if (i==2)
		{
			direction = direction*(-1) - 90;
			ball_controller = false;
		}

	}
	else{}


	if (illusion.is_effect_on())
	{
		if (fake_ball.getCircle().getGlobalBounds().intersects(player1.getShape().getGlobalBounds()) || fake_ball.getCircle().getGlobalBounds().intersects(player1.getShape().getGlobalBounds()))
		{
			illusion.end_duration();
		}
		else if (fake_ball.getcenterx() <= player1posx + (rect_width * 0.7) || cBall.getcenterx() >= player2posx - (rect_width * 0.3))
			illusion.end_duration();

	}


	P1moveup = false; P2moveup = false; P1movedown = false; P2movedown = false;
	//std::cout << direction << std::endl;
	return direction;
}


