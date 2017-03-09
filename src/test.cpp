#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "pingRectangle.h"
#include "gamecircle.h"
#include <math.h>
#define player1posx 20
#define player2posx 950
#define radius 20
#include "gamePowerup.h"
#define rect_width 30
#define windowlength 1000
#define windowheight 600
#include <sstream>
#include "gamestart.h"
#define max_Score 10
#include "gameend.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Image.hpp>


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
sf::Texture texture;
sf::Text info;
sf::Text mScore1,mScore2;
std::string player1_Name = "Madara uchiha", player2_Name = "Hashirama Senju";

gameCircle cBall(100,100,20);
gameCircle fake_ball;
pingRectangle barrier;
sf::CircleShape circle = cBall.getCircle();
pingRectangle player1(player1posx,150, rect_width,rectLength);
pingRectangle player2(player2posx,150, rect_width,rectLength);
pingRectangle rect_up(0,30,windowlength,10,1);
pingRectangle rect_down(0,windowheight - 30,windowlength,10,1);
sf::RectangleShape mBoundaryUp = rect_up.getShape();
sf::RectangleShape mBoundaryDown = rect_down.getShape();
sf::Sprite background;
Obstacle Powerup1(1);
Obstacle Powerup2(2);
Powerup power_invis("invis.png");
Powerup power_diminish("diminish.png");
Powerup illusion("illusion.png");
Powerup restriction("restriction.png");
Powerup Magnet("restriction.png");
sf::Font font2;
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
    std::cout<<cBall.getcenterx() <<"   " <<cBall.getcentery()<<std::endl;
    std::ifstream ifs("myfile.txt");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>() ) );

    sf::RenderWindow win(sf::VideoMode(windowlength, windowheight), "SFML Test");
    win.setActive(false);
    gameStart s("Ping Pong Game","New Game","Set PlayerName",content,&win);
    if(s.getPLayer1() != "")player1_Name = s.getPLayer1();
    if(s.getPLayer2() != "")player2_Name = s.getPLayer2();
    sf::Thread t(&display);
    sf::Thread pad1(&controlpad1);
    sf::Thread pad2(&controlpad2);
	sf::Thread obstac(&powerthread);
	if (!font.loadFromFile("3Dumb.ttf"))
	{

	}
	if(!font2.loadFromFile("EraserRegular.ttf")){}
	mScore1.setFont(font);
	mScore2.setFont(font);
	mScore1.setCharacterSize(20);
	mScore2.setCharacterSize(20);
	mScore1.setFillColor(sf::Color::Blue);
	mScore2.setFillColor(sf::Color::Blue);
	mScore1.setPosition(0,0);
	mScore2.setPosition(windowlength - 30,0);
	t.launch();
	pad1.launch();
	pad2.launch();
	obstac.launch();

    if(!texture.loadFromFile("backGround.png"))
    {

    }
    background.setTexture(texture);
	//if(!background.loadFromFile("backGround.png")){}

	if (!music.openFromFile("narutotheme.ogg"))
	{
		std::cout << "error\n";
	}
	int volume = s.getVolume();
	music.setVolume(volume);
	if(s.getMusicSetting() && s.isVisited())
        music.play();
	if(s.isVisited())velocity = s.getVelocity();
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

		if (!_end)
        {
            draw_shape(win);
        }
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

void MagnetEfect()
{
    for(int i = 0;i < 10 ; i++)
    {
        if(i == 0)
        {
            Magnet.setpowerup();
            //Magnet.getpowerup().getCircle().setFillColor(sf::Color::Red);
        }
        else if(Magnet.is_powerup_on() && i == 10)
        {
            Magnet.setpowerupfree();
        }
        Sleep(1000);
    }


}

void illusion_effect()
{
	for (int i = 0; i < 11; i++)
	{
		if (i == 0)
		{
			illusion.setpowerup();
		}
		else if (illusion.is_powerup_on() && i == 10)
		{
			illusion.setpowerupfree();
		}
		Sleep(1000);
	}
}

void invis_effect()
{
	int duration = 0;
	for (int i = 0; i <16 ; i++)
	{
		if (duration > 0)
		{
			duration--;
			if (duration == 0) power_invis.end_duration();
		}
		if (i ==0)
		{
			power_invis.setpowerup();
		}
		else if (power_invis.is_powerup_on() && i  == 10)
		{
			power_invis.setpowerupfree();
			break;
		}
		if ((power_invis.is_p1_affected() || power_invis.is_p2_affected()) && duration == 0)
		{
			duration = 5;
		}
		Sleep(1000);
	}
}

void diminish_effect()
{
	int duration=0;
	for (int i = 0; i <21 ; i++)
	{
		if (duration > 0)
		{
			duration--;
			if (duration == 0)
			{
				if (power_diminish.is_p1_affected()) player1.scale(1.0, 2.0);
				else player2.scale(1.0, 2.0);
				power_diminish.end_duration();

			}
		}
		if (i == 0)
		{
			power_diminish.setpowerup();
		}
		else if (power_diminish.is_powerup_on() && i == 10)
		{
			power_diminish.setpowerupfree();
			break;
		}
		if ((power_diminish.is_p1_affected() || power_diminish.is_p2_affected()) && duration == 0)
		{
			duration = 10;
		}
		Sleep(1000);
	}
}

void speed_effect()
{
	int duration=0;
	for (int i = 0; i < 16; i++)
	{
		if (duration > 0)
		{
			duration--;
			if (countdown) countdown--;
			if (duration == 10)
			{
				speed_brag = false;
				velocity = 4;
			}
			if (duration == 0) velocity = 2;
		}
		if (i ==0)
		{
			speed_brag = true;
			duration = 15;
			countdown = 5;
		}
		Sleep(1000);
	}
}

void obstacle_effect()
{
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
			Powerup1.setObstacle();
		if (i == 3)
			Powerup1.setobstaclefree();
		if (i == 1)
			Powerup2.setObstacle();
		if (i == 4)
			Powerup2.setobstaclefree();
		Sleep(1000);
	}
}

void restrict_effect()
{
	int duration = 0;
	for (int i = 0; i < 21; i++)
	{
		if (duration > 0)
		{
			duration--;
			if (duration == 0)
				restriction.end_duration();

		}
		if (i ==0)
		{
			restriction.setpowerup();
		}
		else if (restriction.is_powerup_on() && i  == 10)
		{
			restriction.setpowerupfree();
			break;
		}
		if ((restriction.is_p1_affected() || restriction.is_p2_affected()) && duration == 0)
			duration = 10;
		Sleep(1000);
	}
}

void powerthread()
{
	for (; true;)
	{
		int choice = rand()%7;
		if (choice == 0) illusion_effect();
		else if (choice == 1) invis_effect();
		else if (choice == 2) speed_effect();
		else if (choice == 3) diminish_effect();
		else if (choice == 4) restrict_effect();
		else if (choice == 5 && !Magnet.is_powerup_on() && !Magnet.is_effect_on()) obstacle_effect();
		else
            MagnetEfect();
		Sleep(1000);
	}
}

void  draw_shape(sf::RenderWindow& window)
{

    window.draw(background);
    window.draw(mBoundaryUp);
    window.draw(mBoundaryDown);
    if (Powerup1._gameObstacle())window.draw(Powerup1.getObstacle());
	if (power_invis.is_powerup_on()) window.draw(power_invis.getsprite());
	if (power_diminish.is_powerup_on()) window.draw(power_diminish.getsprite());
    if (!power_invis.is_p2_affected())window.draw(player2.getShape());
	if (!power_invis.is_p1_affected()) window.draw(player1.getShape());
    window.draw(cBall.getCircle());
	if (Powerup2._gameObstacle()) window.draw(Powerup2.getObstacle());
	if (illusion.is_powerup_on()) window.draw(illusion.getsprite());
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
    if (restriction.is_powerup_on()) window.draw(restriction.getsprite());

	if (restriction.is_effect_on() || restriction.is_p2_affected() || restriction.is_p1_affected())
        window.draw(barrier.getShape());

    if(Magnet.is_powerup_on())
        window.draw(Magnet.getsprite());
    mScore1.setString(convert(score_left));
    mScore2.setString(convert(score_right));
    window.draw(mScore1);
    window.draw(mScore2);
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
            else if(player1.getposy() <= 40){}
            else
               player1.movePad(0,-5);
            up = false;
        }

        if (down)
        {
            if(player1.getposy() >= windowheight - 30 -rectLength){}
            else
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
            else if (player2.getposy() <= 40){}
            else
                player2.movePad(0,-5);
            player2up = false;
        }

        if (player2down)
        {

             if(player2.getposy() >= windowheight - 30 - rectLength){}
             else
              player2.movePad(0,5);
             player2down = false;
        }
    }
}

int _getDirection()
{

    if(Magnet.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(Magnet.getsprite().getGlobalBounds()))
    {
        Magnet.setpowerupfree();
        if(ball_controller)
            Magnet.take_effect(2);
        else
            Magnet.take_effect(1);
    }

    if (restriction.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(restriction.getsprite().getGlobalBounds()) )
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

	if (illusion.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(illusion.getsprite().getGlobalBounds()) )
	{
		std::cout << "illusion on\n0";
		illusion.setpowerupfree();
		illusion.take_effect(1);
		fake_ball = gameCircle(cBall.getcenterx(), cBall.getcentery(), 20);
		fake_ball.diren = direction + rand() % 10 +20;
		if (fake_ball.diren > 180) fake_ball.diren -= 360;
		else if (fake_ball.diren < -180) fake_ball.diren += 360;

	}
	if (power_invis.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(power_invis.getsprite().getGlobalBounds()))
	{
		power_invis.setpowerupfree();
		if(ball_controller)power_invis.take_effect(2);
		else power_invis.take_effect(1);

	}
	if (power_diminish.is_powerup_on() && cBall.getCircle().getGlobalBounds().intersects(power_diminish.getsprite().getGlobalBounds()))
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
		if(Magnet.is_effect_on() && Magnet.is_p1_affected())
            Magnet.end_duration();
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
		if(Magnet.is_effect_on() && Magnet.is_p2_affected())
            Magnet.end_duration();
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
	else if (cBall.getCircle().getGlobalBounds().intersects(mBoundaryDown.getGlobalBounds()) || cBall.getCircle().getGlobalBounds().intersects(mBoundaryUp.getGlobalBounds()) )
	{
		direction *= -1;
	}

	else if (cBall.getcenterx() <= player1posx + (rect_width * 0.5) || cBall.getcenterx()>= player2posx + (rect_width* 0.5))
	{
	    std::cout<<std::endl<<cBall.getcenterx()<<" " << player2posx + (rect_width* 0.5)<<std::endl;
	    if(cBall.getcenterx() <= player1posx + (rect_width * 0.5))
            score_right ++;
        else
            score_left ++;

        if(Magnet.is_effect_on())
            Magnet.end_duration();

		cBall.reset();
		if(illusion.is_effect_on())
            illusion.end_duration();
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
		else if (fake_ball.getcenterx() <= player1posx + (rect_width * 0.5) || cBall.getcenterx() >= player2posx - (rect_width * 0.5))
			illusion.end_duration();

        if (fake_ball.getCircle().getGlobalBounds().intersects(mBoundaryDown.getGlobalBounds()) ||fake_ball.getCircle().getGlobalBounds().intersects(mBoundaryUp.getGlobalBounds()) )
            fake_ball.diren *= -1;
	}


	if(Magnet.is_effect_on())
    {
        if(Magnet.is_p1_affected())
        {
            double x_diff = player1posx - cBall.getcenterx();
            double y_diff = player1.getposy() + rectLength/2 - cBall.getcentery();
            direction = (int)(atan(y_diff/x_diff) * 180 / 3.1416);
            if(direction >= 0 )
                direction = 180 - direction;
            else
                direction = -180 - direction;
        }
        else
        {
            double x_diff = player2posx - cBall.getcenterx();
            double y_diff = player2.getposy() + rectLength/2 - cBall.getcentery();
            direction = (int)(atan(-y_diff/x_diff) * 180 / 3.1416);
        }
    }

	P1moveup = false; P2moveup = false; P1movedown = false; P2movedown = false;
	return direction;
}


