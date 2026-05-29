#include "Game.h"

Game::Game():win(sf::VideoMode(800, 600), "Connect 4")
{
    state = menu;
    clicked = false;
    redTurn = true;
    enterPressed = false;

    font.loadFromFile("opensans.ttf");
    PlayMove.reserve(12);

    Winner.setFont(font);
    Winner.setCharacterSize(50);
    Winner.setPosition(sf::Vector2f(20, 375));
    Winner.setFillColor(sf::Color::White);

    // Loading Board
    int x = 0, y = 0;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            Container[i][j].setRadius(20);
            Container[i][j].setPosition(sf::Vector2f(50 + x, 550 - y));
            Container[i][j].setFillColor(sf::Color::White);
            y += 60;
        }
        PlayMove.emplace_back(sf::Vector2f(40, 20), "Place", sf::Vector2f(50 + x, 550 - y), font, 15);
        x += 60;
        y = 0;
    }

    // Loading Startup
    UI.reserve(3);

    UI.emplace_back(sf::Vector2f(200, 50), "Play Vs AI", sf::Vector2f(50, 410), font, 40);     // Play Vs AI
    UI.emplace_back(sf::Vector2f(300, 50), "Play Vs Human", sf::Vector2f(50, 470), font, 40);  // Play Vs Human
    UI.emplace_back(sf::Vector2f(100, 50), "Exit", sf::Vector2f(50, 530), font, 40);       // Exit
}

void Game::run()
{
    while(win.isOpen())
    {
        eventHandle();
        if (state == menu)
        {
            startup();
        }
        else if (state == redWin)
        {
            victory("Red Wins");
        }
        else if (state == blueWin)
        {
            victory("Blue Wins");
        }
        else
        {
            if (redTurn)
            {
                playerTurn();
            }
            else
            {
                enemyTurn();
            }
            renderGrid();
        }
    }
}

void Game::eventHandle()
{
    sf::Event e;
    clicked = false;
    enterPressed = false;

    while(win.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            win.close();
        }

        if (e.type == sf::Event::MouseButtonPressed)
        {
            clicked = true;
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
        {
            enterPressed = true;
        }
    }
}

void Game::renderGrid()
{
    win.clear(sf::Color::Black);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            win.draw(Container[i][j]);
        }
        win.draw(PlayMove[i].getbody());
        win.draw(PlayMove[i].gettext());
    }

    win.display();
}

void Game::startup()
{
    // Check Button Click
    if (clicked)
    {
        if (UI[0].isPressed(win))
        {
            state = vsAI;
        }
        else if (UI[1].isPressed(win))
        {
            state = vsHuman;
        }
        else if (UI[2].isPressed(win))
        {
            win.close();
        }
    }
    // Render Start Menu
    win.clear(sf::Color::Black);

    for (int i = 0; i < 3; i++)
    {
        win.draw(UI[i].getbody());
        win.draw(UI[i].gettext());
    }

    win.display();
}

void Game::playerTurn()
{
    if (clicked && redTurn)
    {
        for (int i = 0; i < 12; i ++)
        {
            if (PlayMove[i].isPressed(win))
            {
                if (placeBall(i)) redTurn = false;
                if (winCheck()) state = redWin;
                return;
            }
        }
    }
}

void Game::enemyTurn()
{
    if (state == vsHuman)
    {
        if (clicked)
        {
            for (int i = 0; i < 12; i ++)
            {
                if (PlayMove[i].isPressed(win))
                {
                    if (placeBall(i)) redTurn = true;
                    if (winCheck()) state = blueWin;
                    return;
                }
            }
        }
    }
    else
    {
        enemyAI();
    }
}

bool Game::placeBall(int i)
{
    for (int j = 0; j < 7; j ++)
    {
        if (Container[i][j].getFillColor() == sf::Color::White)
        {
            if (redTurn) Container[i][j].setFillColor(sf::Color::Red);
            else Container[i][j].setFillColor(sf::Color::Blue);
            return true;
        }
    }
    return false;
}

bool Game::winCheck()
{
    int countA = 0, countB = 0, countC = 0, countD = 0;
    for (int j = 0; j < 7; j ++)
    {
        for (int i = 0; i < 12; i ++)
        {
            for (int n = 0; n < 4; n ++)
            {
                if (Container[i][j].getFillColor() != sf::Color::White)
                {
                    if (j < 4)
                    {
                        if (i < 3)
                        {
                            if (Container[i][j].getFillColor() == Container[i + n][j].getFillColor()) countA += 1;
                            if (Container[i][j].getFillColor() == Container[i][j + n].getFillColor()) countB += 1;
                            if (Container[i][j].getFillColor() == Container[i + n][j + n].getFillColor()) countC += 1;
                        }
                        else if (i >= 3 && i < 9)
                        {
                            if (Container[i][j].getFillColor() == Container[i + n][j].getFillColor()) countA += 1;
                            if (Container[i][j].getFillColor() == Container[i][j + n].getFillColor()) countB += 1;
                            if (Container[i][j].getFillColor() == Container[i + n][j + n].getFillColor()) countC += 1;
                            if (Container[i][j].getFillColor() == Container[i - n][j + n].getFillColor()) countD += 1;
                        }
                        else
                        {
                            if (Container[i][j].getFillColor() == Container[i - n][j + n].getFillColor()) countD += 1;
                            if (Container[i][j].getFillColor() == Container[i][j + n].getFillColor()) countB += 1;
                        }
                    }
                    else
                    {
                        if (Container[i][j].getFillColor() == Container[i + n][j].getFillColor()) countA += 1;
                    }
                }
            }
            if (countA == 4 || countB == 4 || countC == 4 || countD == 4) return true;
            else
            {
                countA = 0;
                countB = 0;
                countC = 0;
                countD = 0;
            }
        }
    }
    return false;
}

void Game::victory(std::string s)
{
    for (int i = 0; i < 12; i ++)
    {
        for (int j = 0; j < 7; j ++)
        {
            Container[i][j].setFillColor(sf::Color::White);
        }
    }

    if (enterPressed)
    {
        state = menu;
    }

    Winner.setString(s);

    win.clear(sf::Color::Black);

    win.draw(Winner);

    win.display();
}

void Game::removeBall(int i)
{
    for (int j = 6; j > -1; j --)
    {
        if (Container[i][j].getFillColor() != sf::Color::White)
        {
            Container[i][j].setFillColor(sf::Color::White);
            return;
        }
    }
}

void Game::enemyAI()
{
    for (int i = 0; i < 12; i++)
    {
        if (placeBall(i))
        {
            if (winCheck())
            {
                state = blueWin;
                return;
            }
            removeBall(i);
        }
    }

    bool alive[12] = {true,true,true,true,true,true,true,true,true,true,true,true};

    redTurn = true;
    for (int i = 0; i < 12; i++)
    {
        if (placeBall(i))
        {
            if (winCheck()) alive[i] = false;
            removeBall(i);
        }
    }
    redTurn = false;

    for (int i = 0; i < 12; i++)
    {
        if (alive[i] && placeBall(i))
        {
            redTurn = true;
            return;
        }
    }

    for (int i = 0; i < 12; i++)
    {
        if (placeBall(i))
        {
            redTurn = true;
            return;
        }
    }
}
