#ifndef GAMECIRCLE_H
#define GAMECIRCLE_H

#include <SFML/Graphics.hpp>


class gameCircle
{
    public:
        gameCircle(float,float,float);
        virtual ~gameCircle();
        float getRadius();
        float getcenterx();
        float getcentery();
        sf::CircleShape getCircle();
        sf::CircleShape setCircle(float);
        void moveball(float,int);
        void reset();
		gameCircle();
		int diren;

    protected:

    private:
        float centerx;
        float centery;
        sf::CircleShape circle;
        float radius;
};

#endif // GAMECIRCLE_H
