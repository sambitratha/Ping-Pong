#ifndef GAMEEND_H
#define GAMEEND_H
#include <SFML/Graphics.hpp>
#include <iostream>

class gameend
{
    public:
		gameend();
        gameend(int,int,std::string,std::string,sf::RenderWindow*);
        virtual ~gameend();
		std::string convert(int);

    protected:

    private:
        void setTextProperties(sf::Text,sf::Font,std::string,int,float,float);

};

#endif // GAMEEND_H
