#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <memory>
#include <optional>

#include "Button.h"

enum class SlotState
{
	Red,
	Blue,
	Empty
};

class Slot
{
	private:
		sf::CircleShape body;
		sf::Vector2f coordinates;
		SlotState state;
		
	public:
		Slot(){}
		Slot(sf::Vector2f & coords);
		bool fill(SlotState newState);
		void draw(sf::RenderWindow & win);
		const SlotState & getState() const; 
};

class Board
{
	private:
		sf::Vector2f lastDrop;
		std::vector<std::vector<std::unique_ptr<Slot>>> slotGrid;
		std::vector<std::unique_ptr<Button>> dropper;
		
	public:
		// Basic Functions
		Board(sf::Font & font);
		void input(const std::optional<sf::Event> & event);
		void draw(sf::RenderWindow & win);
		
		// Gameplay Methods
		bool drop(int colIndex, SlotState state);
		bool isFilled();
		void reset();
		
		// Getter
		const std::vector<std::vector<std::unique_ptr<Slot>>> & getSlotGrid() const;
		const sf::Vector2f & getLastDrop() const;
		Button & getButton(int index);
};