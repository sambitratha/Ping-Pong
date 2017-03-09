#ifndef GAMESTART_H
#define GAMESTART_H


#include <SFML/Graphics.hpp>



class gameStart
{
    public:
        gameStart( std::string greetings , std::string option1 , std::string option2 , std::string instructions ,sf::RenderWindow* windo);
        virtual ~gameStart();
        //void drawWindow(sf::RenderWindow* windo);
        bool getData();
        std::string getPLayer1();
        std::string getPLayer2();
        void setInstructionPage(sf::RenderWindow* win,std::string msg);
        bool getMusicSetting();
        int getVolume();
        float getVelocity();
        bool isVisited();

    protected:

    private:

        sf::RenderWindow* window;
        sf::Text _greetingText;
        sf::Text _newGame;
        sf::Text _setPlayerName;
        bool Start ;
        bool isfinished ;
        bool isPlayerName;
        std::string _player1Name;
        std::string _player2Name;
        bool player1 ;
        bool player2 ;
        int i , j;
        sf::Font font ;
        sf::Font font1 ;
        sf::Font font2 ;
        bool music;
        int volume;
        int velocity;
        bool visited = false;

};

#endif // GAMESTART_H
