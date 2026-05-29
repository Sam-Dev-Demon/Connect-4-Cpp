#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
    public:
        Button(sf::Vector2f s, std::string t, sf::Vector2f p, sf::Font & f, int ts);
        bool isHovered(sf::RenderWindow & win);
        bool isPressed(sf::RenderWindow & win);
        sf::RectangleShape getbody();
        sf::Text gettext();

    private:
        sf::RectangleShape body;
        sf::Text text;
};
