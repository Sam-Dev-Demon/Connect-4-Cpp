#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Button.h"

class Game
{
    public:
        Game();
        void run();

    private:
        sf::Font font;
        sf::Text Winner;

    private:
        sf::RenderWindow win;
        sf::CircleShape Container[12][7];
        std::vector <Button> PlayMove;
        std::vector <Button> UI;

    private:
        enum states {menu, vsAI, vsHuman, redWin, blueWin};
        int state;
        bool clicked;
        bool redTurn;
        bool enterPressed;

    private:
        void startup();
        void renderGrid();
        void eventHandle();

    private:
        void playerTurn();
        void enemyTurn();

    private:
        void enemyAI();

    private:
        bool placeBall(int i);
        void removeBall(int i);
        bool winCheck();
        void victory(std::string s);
};
