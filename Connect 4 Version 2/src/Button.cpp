#include "Button.h"

Button::Button(sf::Vector2f pos, unsigned int size, std::string txt, sf::Font & font)
{
	text = std::make_unique<sf::Text>(font, txt, size);
	text->setPosition(sf::Vector2f(pos.x - 5, pos.y - 5));
	text->setFillColor(sf::Color(0, 0, 0, 255));
	mouseClicked = false;
	
	sf::Color temp(80, 230, 155, 204);
	display.bodyA.setPosition(sf::Vector2f(pos.x - 5, pos.y - 5));
	display.bodyA.setSize(text->getGlobalBounds().size + sf::Vector2f(size/5, size/5));
	display.bodyA.setFillColor(temp);
	
	float r = display.bodyA.getSize().y/2;
	display.bodyB1.setPosition(display.bodyA.getPosition() + sf::Vector2f(-r, 0));
	display.bodyB1.setRadius(r);
	display.bodyB1.setFillColor(temp);
	
	display.bodyB2.setPosition(sf::Vector2f(display.bodyA.getPosition().x + display.bodyA.getSize().x - r, display.bodyA.getPosition().y));
	display.bodyB2.setRadius(r);
	display.bodyB2.setFillColor(temp);
	
	display.body.setPosition(display.bodyB1.getPosition());
	display.body.setSize(display.bodyA.getSize() + sf::Vector2f(2 * r, 0));
	display.body.setFillColor(sf::Color(0, 0, 0, 0));
}

void Button::update(const std::optional<sf::Event> & event)
{
	mouseClicked = false;
	if (event->is<sf::Event::MouseButtonReleased>() && 
		event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
	{
		mouseClicked = true;
	}
}

bool Button::isHovered(sf::RenderWindow & win)
{
	return display.body.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(win).x), static_cast<float>(sf::Mouse::getPosition(win).y)));
}

bool Button::isClicked(sf::RenderWindow & win)
{
	bool val = isHovered(win) && mouseClicked;
	mouseClicked = false;
	return val;
}

void Button::draw(sf::RenderWindow & win)
{
	win.draw(display.bodyA);
	win.draw(display.bodyB1);
	win.draw(display.bodyB2);
	win.draw(*text);
}