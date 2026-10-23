#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <memory>

#include "Button.h"

enum class State
{
	Menu,
	vsAI,
	vsHuman
};

class Menu
{
	private:
		std::vector<Button> button;
		std::unique_ptr<sf::Text> title;
	
	public:
		Menu(sf::Font & font);
		void input(const std::optional<sf::Event> & event);
		State process(sf::RenderWindow & win);
		void render(sf::RenderWindow & win);
};