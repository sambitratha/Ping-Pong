#include "gamestart.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game_settings.h"
#include "instructionpage.h"

gameStart::gameStart(std::string greetings , std::string option1 , std::string option2,std::string instructions ,sf::RenderWindow* window)
{
    i = 0;
    j = 0;
    isPlayerName = false;
    isfinished = false ;
    player1 = false;
    player2= false;
    Start = true;
    isfinished = false;
    std::cout<<"started\n";

    std::string a[3] = {"Music","Volume","Velocity"};
    std::string b[3] = {"ON","12","2"};
    sf::Texture textureUp;
    sf::Texture textureDown;
    if(!textureUp.loadFromFile("uparrow.png"))
    {

    }
    window->setActive(false);
    sf::Sprite uparrow;
    uparrow.setTexture(textureUp);
    uparrow.setTextureRect(sf::IntRect(30, 10, 50, 50));
    uparrow.setColor(sf::Color::Red);
    uparrow.setPosition(330,190);
    if(!textureDown.loadFromFile("downarrow.png"))
    {

    }
    sf::Sprite downarrow;
    downarrow.setTexture(textureDown);
    downarrow.setTextureRect(sf::IntRect(30, 35, 50, 50));
    downarrow.setColor(sf::Color::Red);
    downarrow.setPosition(330,280);
    if(!font.loadFromFile("3Dumb.ttf"))
    {

    }
    if(!font1.loadFromFile("Xanadu.ttf"))
    {

    }
    if(!font2.loadFromFile("EraserRegular.ttf"))
    {

    }

    sf::Text player1Name;
    sf::Text player2Name;
    sf::Text Settingsicon;
    sf::Text Instructionsicon;
    sf::Text Settings;
    sf::Text Instructions;
    sf::Text directions;

    directions.setFont(font2);
    directions.setString("Press Left Arrow for PLayer1 \n\n\nPress Right Arrow for player2 ");
    directions.setCharacterSize(20);
    directions.setFillColor(sf::Color::Yellow);
    directions.setPosition(300,150);


    player1Name.setFont(font1);
    player1Name.setString("Enter player1 Name: " + _player1Name);
    player1Name.setCharacterSize(24);
    player1Name.setFillColor(sf::Color::Red);
    player1Name.setPosition(400,150);

    player2Name.setFont(font1);
    player2Name.setString("Enter player2 Name: " + _player2Name);
    player2Name.setCharacterSize(24);
    player2Name.setFillColor(sf::Color::Red);
    player2Name.setPosition(400,150);

    _greetingText.setFont(font);
    _greetingText.setString(greetings);
    _greetingText.setCharacterSize(35);
    _greetingText.setFillColor(sf::Color::Red);
    _greetingText.setPosition(400,50);

    _newGame.setFont(font);
    _newGame.setString(option1);
    _newGame.setCharacterSize(30);
    _newGame.setFillColor(sf::Color::Red);
    _newGame.setPosition(400,200);

    _setPlayerName.setFont(font);
    _setPlayerName.setString(option2);
    _setPlayerName.setCharacterSize(30);
    _setPlayerName.setFillColor(sf::Color::Red);
    _setPlayerName.setPosition(400,280);

    Settingsicon.setFont(font1);
    Settingsicon.setString("M");
    Settingsicon.setCharacterSize(35);
    Settingsicon.setFillColor(sf::Color::Red);
    Settingsicon.setPosition(340,360);

    Settings.setFont(font);
    Settings.setString("Settings");
    Settings.setCharacterSize(35);
    Settings.setFillColor(sf::Color::Red);
    Settings.setPosition(400,360);

    Instructionsicon.setFont(font1);
    Instructionsicon.setString("N");
    Instructionsicon.setCharacterSize(35);
    Instructionsicon.setFillColor(sf::Color::Red);
    Instructionsicon.setPosition(340,420);

    Instructions.setFont(font);
    Instructions.setString("Instructions");
    Instructions.setCharacterSize(35);
    Instructions.setFillColor(sf::Color::Red);
    Instructions.setPosition(400,420);
    std::cout<<"finished\n";
    while(window->isOpen() && !isfinished)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if( isPlayerName == false )isfinished = true;
                else
                {
                    Start = true;
                    isPlayerName = false;
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                isPlayerName = true ;
                Start = false;
            }

            if(isPlayerName && !player1 && !player2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player1 = true ;


            else if (isPlayerName && player1 && !player2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player1 = false;

            if(isPlayerName && !player1 && !player2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player2 = true ;

            else if (isPlayerName && !player1 && player2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player2 = false;

            if (isPlayerName && player1 && !player2 && event.type == sf::Event::TextEntered)
                    _player1Name += (char)event.text.unicode;


            if (isPlayerName && !player1 && player2 && event.type == sf::Event::TextEntered)
                    _player2Name += (char)event.text.unicode;


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !player1 && !player2)
                InstructionPage mInstructions(window,instructions);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !player1 && !player2)
            {
                std::cout<<"called";
                visited = true;
                game_settings s( a , b ,window );
                music = s.getMusicSetting();
                volume = s.getVolume();
                velocity = s.getVelocity();

            }


            std::cout<<"isPlayerName = "<<isPlayerName<<"  start= : "<<Start<<"   player1: "<<player1<<"   player2: "<<player2<<"\n";
        }
        player1Name.setString("Enter player1 Name: \n" +_player1Name);
        player2Name.setString("Enter player1 Name: \n" +_player2Name);
        window->clear();
        if(Start)window->draw(_greetingText);
        if(Start)window->draw(_newGame);
        if(Start)window->draw(Settings);
        if(Start)window->draw(Settingsicon);
        if(Start)window->draw(Instructions);
        if(Start)window->draw(Instructionsicon);
        if(Start)window->draw(uparrow);
        if(Start)window->draw(downarrow);
        if(!isPlayerName && !player1 && !player2)window->draw(_setPlayerName);
        if(isPlayerName && !player1 && !player2) window -> draw(directions);
        if(isPlayerName && player1 && !player2)
        {
            window ->draw( player1Name);

        }
        if(isPlayerName && !player1 && player2) window ->draw( player2Name);

        window->display();
    }

}

bool gameStart::getData()
{
    return isfinished;
}

std::string gameStart::getPLayer1()
{
    return _player1Name;
}
std::string gameStart::getPLayer2()
{
    return _player2Name;
}

gameStart::~gameStart()
{
    //dtor
}

void gameStart::setInstructionPage(sf::RenderWindow* window,std::string message)
{

    sf::Text instructions;
    instructions.setFont(font1);
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color::Blue);
    instructions.setString(message);
    instructions.setPosition(300,100);
    bool is_instruction_on = true;
    int x = 0;
    while(window->isOpen() && is_instruction_on)
    {
        sf::Event event;
        while(window->pollEvent(event))
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                is_instruction_on = false;
        }
        if(x == 0)
        {
            window->clear();
            window->draw(instructions);
            x++;
        }

        window->display();
    }
}


bool gameStart::getMusicSetting()
{
    return music;
}
int gameStart::getVolume()
{
    return volume;
}
float gameStart::getVelocity()
{
    return velocity;
}
bool gameStart::isVisited()
{
    return visited;
}
