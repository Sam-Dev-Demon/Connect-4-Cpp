#include "Game.h"

void Game::gameReset()
{
	victory = SlotState::Empty;
	state = State::Menu;
	turn = Turn::Red;
	board->reset();
	logic->reset();
}

void setWinText(std::unique_ptr<sf::Text> & winText, std::unique_ptr<sf::Text> & winText2, sf::Font & font)
{
	winText = std::make_unique<sf::Text>(font, "X", 150);
	winText->setPosition(sf::Vector2f(100, 100));
	winText->setFillColor(sf::Color(255, 255, 255, 255));
	winText->setOutlineColor(sf::Color(0, 0, 0, 255));
	winText->setOutlineThickness(15);
	
	winText2 = std::make_unique<sf::Text>(font, "Press Enter to continue", 20);
	winText2->setPosition(sf::Vector2f(100, 500));
	winText2->setFillColor(sf::Color(255, 255, 255, 255));
	winText2->setOutlineColor(sf::Color(0, 0, 0, 255));
	winText2->setOutlineThickness(3);
}

Game::Game() : win(sf::VideoMode({800, 600}), "Connect 4")
{
	// Load Font
	font.openFromFile(ROOT"opensans.ttf"); // ROOT is a string literal defined in CMakeLists.txt
	
	// Set Game Components
	board = std::make_unique<Board>(font);
	menu = std::make_unique<Menu>(font);
	logic = std::make_unique<Logic>(*board);
	
	// Set Game States
	gameReset();
	
	// Set winText
	setWinText(winText, winText2, font);
}

void Game::input()
{
	while (const std::optional event = win.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			win.close();
		
		if (state == State::Menu)
			menu->input(event);
		else if (!board->isFilled() && victory == SlotState::Empty)
			board->input(event);
		else if (event->is<sf::Event::KeyPressed>() &&
			event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Enter)
			gameReset();
	}
}

void Game::process()
{
	if (state == State::Menu)
		state = menu->process(win);
	else
	{
		if (!board->isFilled() && victory == SlotState::Empty)
		{
			if (turn == Turn::Red)
			{
				humanPlay();
			}
			else 
			{
				if (state == State::vsAI)
					AIPlay();
				else
					humanPlay();
			}
		}
		else if (victory == SlotState::Empty)
			winText->setString("Draw");
		else if (victory == SlotState::Red)
			winText->setString("Red Wins");
		else 
			winText->setString("Blue Wins");
	}
}

void Game::render()
{
	win.clear(sf::Color(190, 255, 125, 204));

	if (state == State::Menu)
		menu->render(win);
	else if (!board->isFilled() && victory == SlotState::Empty)
		board->draw(win);
	else
	{
		win.draw(*winText);
		win.draw(*winText2);
	}

	win.display();
}

void Game::run()
{
	while(win.isOpen())
	{
		input();
		process();
		render();
	}
}

void Game::humanPlay()
{
	for (int i = 0; i < 7; i ++)
	{
		if (board->getButton(i).isClicked(win))
		{
			if (turn == Turn::Red)
			{
				if (board->drop(i, SlotState::Red))
					turn = Turn::Blue;
			}
			else if (board->drop(i, SlotState::Blue))
				turn = Turn::Red;
			victory = logic->winCheck();
		}
	}
}

void Game::AIPlay()
{
	int i = logic->evaluate();
	board->drop(i, SlotState::Blue);
	victory = logic->winCheck();
	turn = Turn::Red;
}