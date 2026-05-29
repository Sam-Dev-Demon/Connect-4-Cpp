#include "Button.h"

Button::Button(sf::Vector2f s, std::string t, sf::Vector2f p, sf::Font &f, int ts)
{
    body.setPosition(p);
    body.setSize(s);
    body.setFillColor(sf::Color::Red);

    text.setFont(f);
    text.setString(t);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(body.getPosition());
    text.setCharacterSize(ts);
}

bool Button::isHovered(sf::RenderWindow & win)
{
    float x1 = body.getPosition().x;
    float y1 = body.getPosition().y;

    float x2 = x1 + body.getSize().x;
    float y2 = y1 + body.getSize().y;

    float x3 = sf::Mouse::getPosition(win).x;
    float y3 = sf::Mouse::getPosition(win).y;

    if (x3 > x1 && x3 < x2 && y3 > y1 && y3 <y2) return true;
    else return false;
}

bool Button::isPressed(sf::RenderWindow & win)
{
    if (isHovered(win) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;
    else return false;
}

sf::RectangleShape Button::getbody()
{
    return body;
}

sf::Text Button::gettext()
{
    return text;
}
