#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <array>
#include "Board.h"

class Logic
{
	private:
		const Board & board;
		std::array<std::array<char, 6>, 7> boardState;
		
	public:
		Logic(const Board & b);
		
		SlotState winCheck();
		static void lineCheck(int & count, int x, int y, char c, sf::Vector2f dir, std::array<std::array<char, 6>, 7> & boardS);
		static sf::Vector2f fullCheck(char c, sf::Vector2f main, std::array<std::array<char, 6>, 7> & bS);
		
		int evaluate();
		std::array<int, 7> findValidPoints(std::array<std::array<char, 6>, 7> & boardCopy);
		std::array<int, 7> setHeuristics(std::array<std::array<char, 6>, 7> & boardCopy, char c, char nC);
		
		void reset();
};