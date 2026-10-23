#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>
#include <array>
#include <optional>
#include <memory>

struct Capsule
{
	sf::RectangleShape bodyA;
	sf::CircleShape bodyB1, bodyB2;
	sf::RectangleShape body;
};

class Button
{
	private:
		Capsule display;
        std::unique_ptr<sf::Text> text;
		bool mouseClicked;
		
    public:
		Button(sf::Vector2f pos, unsigned int size, std::string txt, sf::Font & f);
        void update(const std::optional<sf::Event> & event);
		bool isClicked(sf::RenderWindow & win);
		bool isHovered(sf::RenderWindow & win);
		void draw(sf::RenderWindow & win);
};
