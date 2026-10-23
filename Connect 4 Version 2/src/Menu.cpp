#include "Menu.h"

Menu::Menu(sf::Font & font)
{
	button.reserve(3);
	button.emplace_back(sf::Vector2f(300, 300), 75, "vsHuman", font);
	button.emplace_back(sf::Vector2f(300, 400), 75, "vsAI", font);
	button.emplace_back(sf::Vector2f(300, 500), 75, "Quit", font);
	
	title = std::make_unique<sf::Text>(font, "Connect 4", 100);
	title->setPosition(sf::Vector2f(200, 100));
	title->setFillColor(sf::Color(255, 255, 255, 255));
	title->setOutlineThickness(10);
	title->setOutlineColor(sf::Color(0, 0, 0, 255));
}

void Menu::input(const std::optional<sf::Event> & event)
{
	for (auto & b : button)
		b.update(event);
}

State Menu::process(sf::RenderWindow & win)
{
	if (button[0].isClicked(win)) return State::vsHuman;
	else if (button[1].isClicked(win)) return State::vsAI;
	else if (button[2].isClicked(win)) win.close();
	return State::Menu;
}

void Menu::render(sf::RenderWindow & win)
{
	for (auto & b : button)
		b.draw(win);
	win.draw(*title);
}