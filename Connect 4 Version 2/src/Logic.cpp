#include "Logic.h"

Logic::Logic(const Board & b) : board(b)
{
	reset();
}

inline int absolute(float x)
{
	return (x > 0)? x : -1 * x;
}

std::array<int, 7> Logic::findValidPoints(std::array<std::array<char, 6>, 7> & boardCopy)
{
	std::array<int, 7> validPoints;
	
	for (int i = 0; i < 7; i ++)
	{
		validPoints[i] = -1;
		for (int j = 5; j > -1; j --)
		{
			if (boardCopy[i][j] == 'X')
			{
				validPoints[i] = j;
				break;
			}
		}
	}
	
	return validPoints;
}

std::array<int, 7> Logic::setHeuristics(std::array<std::array<char, 6>, 7> & boardCopy, char c, char nC)
{
	std::array<int, 7> heuristics;

	for (auto & x : heuristics)
			x = 0;
	
	for (int i = 0; i < 7; i ++)
	{
		for (int j = 0; j < 6; j ++)
		{
			if (boardCopy[i][j] != 'X' || boardCopy[i][j - 1] == 'X')
				continue;
			for (int k = -1; k < 2; k ++)
			{
				if (i + k < 0 || i + k >= 7)
					continue;
				for (int l = -1; l < 2; l ++)
				{
					if (j + l < 0 || j + l >= 6 || (i == 0 && j == 0))
						continue;
					int c1 = 0, c2 = 0, c3 = 0;
					lineCheck(c1, i, j, c, sf::Vector2f(k, l), boardCopy);
					lineCheck(c2, i, j, 'X', sf::Vector2f(k, l), boardCopy);
					lineCheck(c3, i, j, nC, sf::Vector2f(k, l), boardCopy);
					heuristics[i] = 4 * c1 + 2 * c2 + c3;
					c1 = 0;
					c2 = 0;
					c3 = 0;
				}
			}
		}
	}
	return heuristics;
}

int Logic::evaluate()
{
	std::array<std::array<char, 6>, 7> boardCopy = boardState;
	std::array<int, 7> validPoints = findValidPoints(boardCopy);
	std::array<int, 7> heuristics;
	int finalIndex = 0;
	
	for (int i = 0; i < 7; i ++)
	{
		boardCopy[i][validPoints[i]] = 'R';
		sf::Vector2f temp = fullCheck('R', sf::Vector2f(i, validPoints[i]), boardCopy);
		boardCopy[i][validPoints[i]] = 'B';
		sf::Vector2f temp2 = fullCheck('B', sf::Vector2f(i, validPoints[i]), boardCopy);
		boardCopy[i][validPoints[i]] = 'X';
		if (absolute(temp.x) >= 4 || absolute(temp.y) >= 4)
			return i;
		else if (absolute(temp2.x) >= 4 || absolute(temp2.y) >= 4)
			return i;
		else
		{
			heuristics = setHeuristics(boardCopy, 'B', 'R');
			finalIndex = (heuristics[i] > heuristics[finalIndex])? i : finalIndex;
		}
	}
	
	return finalIndex;
}

SlotState Logic::winCheck()
{
	sf::Vector2f main = board.getLastDrop();
	const Slot s = *board.getSlotGrid()[main.x][main.y];
	
	if (s.getState() == SlotState::Empty)
		return SlotState::Empty;
	
	boardState[main.x][main.y] = (s.getState() == SlotState::Red)? 'R' : 'B';
	char c = boardState[main.x][main.y];
	
	sf::Vector2f temp = fullCheck(c, main, boardState);
	if (absolute(temp.x) >= 4 || absolute(temp.y) >= 4)
		return (c == 'R')? SlotState::Red : SlotState::Blue;
	
	return SlotState::Empty;
}

sf::Vector2f Logic::fullCheck(char c, sf::Vector2f main, std::array<std::array<char, 6>, 7> & bS)
{
	sf::Vector2f temp(0, 0);
	
	int count = 0;
	int lineCount[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	int maxCount = 1;
	for (int i = -1; i < 2; i ++)
	{
		for (int j = -1; j < 2; j ++)
		{
			if (i == 0 && j == 0)
				continue;
			lineCheck(count, main.x, main.y, c, sf::Vector2f(i, j), bS); // Modifies count
			if (count >= 4)
				return sf::Vector2f(count * i, count * j); 
			else
			{
				lineCount[i + 1][j + 1] = count;
				maxCount = (count > maxCount)? count : maxCount;
				count = lineCount[i + 1][j + 1] + lineCount[1 - i][1 - j] - 1;
				
				if (count >= 4)
					return sf::Vector2f(count * i, count * j);
				
				temp = sf::Vector2f(maxCount * i, maxCount * j);
				count = 0;
			}
		}
	}
	
	return temp;
}



void Logic::lineCheck(int & count, int x, int y, char c, sf::Vector2f dir, std::array<std::array<char, 6>, 7> & boardS)
{
	if (x < 0 || x >= 7 || y < 0 || y >= 6 || count >= 4 || boardS[x][y] != c)
		return;

	count ++;
	x += dir.x;
	y += dir.y;
	
	lineCheck(count, x, y, c, dir, boardS);
}


void Logic::reset()
{
	for (auto & i : boardState)
		for (auto & j : i)
			j = 'X';
}