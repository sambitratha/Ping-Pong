#ifndef PINGRECTANGLE_H
#define PINGRECTANGLE_H

#include <SFML/Graphics.hpp>

class pingRectangle
{
    public:
        pingRectangle();
        pingRectangle(int,int,int,int);
        pingRectangle(int,int,int,int,int);
        sf::RectangleShape getShape();
        void scale(float,float);
        int getWidth();
        int getHeight();
        float getposx();
        float getposy();
        sf::RectangleShape createRect(float,float);
        void movePad(float x ,float y);


    protected:

    private:
        float width;
        float height;
        float posx;
        float posy;
        sf::RectangleShape rect;
};

#endif // PINGRECTANGLE_H
