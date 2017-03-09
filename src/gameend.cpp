#include "gameend.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <SFML/Audio.hpp>
#include <windows.h>

gameend::gameend(int score1,int score2,std::string firstPlayer,std::string secondPlayer ,sf::RenderWindow* window)
{

    sf::SoundBuffer Sound;
    Sound.loadFromFile("bird.wav");

    sf::Sound SFX(Sound);
    SFX.play();

    std::string winner;
    if(score1 > score2)
        winner = firstPlayer;
    else if (score1 < score2)
        winner = secondPlayer;
    else
        winner = "woah!! there's a tie";
    sf::Text player1;
    sf::Text player2;
    sf::Text result;
    sf::Text endMessage;

    sf::Font font;
    sf::Font font1;
    sf::Font font2;


    if(!font.loadFromFile("3Dumb.ttf"))
    {

    }
    if(!font1.loadFromFile("Xanadu.ttf"))
    {

    }
    if(!font2.loadFromFile("EraserRegular.ttf"))
    {

    }


    //setTextProperties(player1,font,firstPlayer+scr1,25,30,200);
    player1.setFont(font1);
    player1.setString(firstPlayer +" scored "+ convert(score1));
    player1.setCharacterSize(15);
    player1.setFillColor(sf::Color::Yellow);
    player1.setPosition(100,200);

    player2.setFont(font1);
    player2.setString(secondPlayer +" scored "+ convert(score2));
    player2.setCharacterSize(15);
    player2.setFillColor(sf::Color::Yellow);
    player2.setPosition(700,200);

    result.setFont(font);
    result.setString(winner + " Won");
    result.setCharacterSize(20);
    result.setFillColor(sf::Color::Red);
    result.setPosition(400,400);

    endMessage.setFont(font2);
    endMessage.setString("Game Over" );
    endMessage.setCharacterSize(45);
    endMessage.setFillColor(sf::Color::Cyan);
    endMessage.setPosition(400,70);


    //setTextProperties(player2,font,secondPlayer+scr2,25,400,200);
    //setTextProperties(result,font2,winner,30,250,400);
    //setTextProperties(endMessage,font1,"Game Over",40,250,70);

    /*endMessage.setColor(sf::Color::Cyan);
    player1.setColor(sf::Color::Yellow);
    player2.setColor(sf::Color::Yellow);
    result.setColor(sf::Color::Red);*/

    while(window->isOpen())
    {
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(player1);
        window->draw(player2);
        window->draw(endMessage);
        window->draw(result);
        window->display();
    }
}

void gameend::setTextProperties(sf::Text text,sf::Font font,std::string displaytext,int size,float posx,float posy)
{
    text.setFont(font);
    text.setString(displaytext);
    text.setCharacterSize(size);
    text.setPosition(posx,posy);
    text.setFillColor(sf::Color::Red);
}

gameend::~gameend()
{
    //dtor
}

gameend::gameend()
{
	//dtor
}

std::string gameend::convert(int a)
{
	std::ostringstream ss;
	ss << a;
	return ss.str();
}
