#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>
#include <memory>
#include <optional>

#include "Menu.h"
#include "Board.h"
#include "Logic.h"

enum class Turn
{
	Red,
	Blue
};

class Game
{
	private:
		// Basic Necessity
		sf::RenderWindow win;
		sf::Font font;
		
		// Game Loop
		void input();
		void process();
		void render();
		
		// Game Componenets
		std::unique_ptr<Board> board;
		std::unique_ptr<Menu> menu;
		std::unique_ptr<Logic> logic;
		
		// Local Items
		std::unique_ptr<sf::Text> winText;
		std::unique_ptr<sf::Text> winText2;
		SlotState victory;
		State state;
		Turn turn;
		
		// Move Deployers
		void humanPlay();
		void AIPlay();
	
		// Reset Game
		void gameReset();
	
	public:
		Game();
		void run();
};