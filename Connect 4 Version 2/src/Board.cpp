#include "Board.h"

// Slot Class

Slot::Slot(sf::Vector2f & coords)
{
	coordinates = coords;
	state = SlotState::Empty;
	
	body.setRadius(25);
	body.setOutlineThickness(5);
	body.setFillColor(sf::Color(0, 0, 0, 50));
	body.setOutlineColor(sf::Color(0, 0, 0, 200));
	body.setPosition(sf::Vector2f(100 + 100 * coords.x, 100 + 67 * coords.y));
}

bool Slot::fill(SlotState newState)
{
	if (state == SlotState::Empty || newState == SlotState::Empty) 
	{
		state = newState;
		if (state == SlotState::Red) body.setFillColor(sf::Color(255, 165, 60, 204));
		else if (state == SlotState::Blue) body.setFillColor(sf::Color(30, 200, 255, 204));
		else body.setFillColor(sf::Color(0, 0, 0, 50));
	}
	else return false;
	return true;
}

void Slot::draw(sf::RenderWindow & win)
{
	win.draw(body);
}

const SlotState & Slot::getState() const
{
	return state;
}

// Board Class

Board::Board(sf::Font & font)
{
	slotGrid.resize(7);
	dropper.resize(7);
	sf::Vector2f coords(0, 0);
	for (auto & x : slotGrid)
	{
		x.resize(6);
		for (auto & y : x)
		{
			y = std::make_unique<Slot>(coords);
			coords.y ++;
		}
		coords.y = 0;
		coords.x ++;
	}
	int it = 1;
	for (auto & i : dropper)
	{
		i = std::make_unique<Button>(sf::Vector2f(100 * it, 520), 20, "Drop", font);
		it ++;
	}
}

void Board::input(const std::optional<sf::Event> & event)
{
	for (auto & i : dropper)
		i->update(event);
}

bool Board::drop(int colIndex, SlotState state)
{
	for (int i = 5; i >= 0; i --)
	{
		if (slotGrid[colIndex][i]->fill(state)) 
		{
			lastDrop = sf::Vector2f(colIndex, i);
			return true;
		}
	}
	return false;
}


void Board::draw(sf::RenderWindow & win)
{
	for (auto & x : slotGrid)
	{
		for (auto & y : x)
		{
			y->draw(win);
		}
	}
	for (auto & i : dropper)
	{
		i->draw(win);
	}
}

bool Board::isFilled()
{
	for (int i = 0; i < 7; i ++)
		if (slotGrid[i][0]->getState() == SlotState::Empty) return false;
	return true;
}

void Board::reset()
{
	for (auto & x : slotGrid)
		for (auto & y : x)
			y->fill(SlotState::Empty);
}

const std::vector<std::vector<std::unique_ptr<Slot>>> & Board::getSlotGrid() const
{
	return slotGrid;
}

const sf::Vector2f & Board::getLastDrop() const
{
	return lastDrop;
}

Button & Board::getButton(int i)
{
	return *dropper[i];
}