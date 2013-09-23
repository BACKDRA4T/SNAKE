#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <deque>
#include <string>

#include "map.hpp"
#include "snake.hpp"

using std::vector;

//Set Game Values
bool isGameOn=true;
bool playerWon=false;

//Width Of Map
const int mapWidth = 800; 
const int mapHeight = 600;
//Instantiate Classes
Map M;
Snake S;

//Start Timers
sf::Clock gameClock;
sf::Clock foodClock;

sf::Time elapsedTime;
sf::Time foodCounter;

//To Do
//Move Collision check into moveSeg code
//Create Win/Lose Scenario
//Create Hud
//Profit??

void updateGame()
{	
	//Move Snake
	S.shiftSeg();
	//Check for Collision
	if(S.checkSnakeCollision(M.accessMap(), (mapWidth/20), (mapHeight/20)))
	{
		isGameOn=false;
	}
	else if(S.getSnakeHeadPos() == M.getFoodPos())
	{
		S.eatFood();
		M.spawnFood();
		foodClock.restart();
	}
}

int initGame()
{
	//Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    sf::VideoMode videoMode(800,600);
    sf::RenderWindow window(videoMode,"SNAKE!!!!", sf::Style::Default, settings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true); // call it once, after creating the window
	sf::Vector2u windowSize = window.getSize();
	unsigned int windowWidth = windowSize.x;
	unsigned int windowHeight = windowSize.y;


	//Load Font
	sf::Font font;
	if(!font.loadFromFile("tomb.ttf"))
	{
		return 01;
	}

	//Load Menu
	sf::Text text;
	text.setFont(font); // font is a sf::Font
	text.setString("Hello world");
	text.setCharacterSize(24); // in pixels, not points!
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	//Make Map
	M.setSizeOfMap(800,600);
	M.createTiles();

	//Spawn Food
	M.spawnFood();

	//Make Snake
	S.createSnake(5);
	S.setDirection(0);

	//Start Game Loop
	gameClock.restart();
	foodClock.restart();

	while (window.isOpen())
    {
		//Handle Events
        sf::Event event;
        while(window.pollEvent(event))
        {
			// check the type of the event...
			switch (event.type)
			{
				// window closed
				case sf::Event::Closed:
					window.close();
					return 1;
					break;
				// key pressed
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape)
					{
						window.close();	
						return 1;
					}
					else if(event.key.code == sf::Keyboard::Up)
					{
						S.setDirection(1);
					}
					else if(event.key.code == sf::Keyboard::Down)
					{
						S.setDirection(2);
					}
					else if(event.key.code == sf::Keyboard::Left)
					{
						S.setDirection(3);
					}
					else if(event.key.code == sf::Keyboard::Right)
					{
						S.setDirection(4);
					}
					break;
				// we don't process other types of events
				default:
					break;
			}
        }


		//Update Game Logic
		elapsedTime = gameClock.getElapsedTime();
		foodCounter = foodClock.getElapsedTime();

		if(elapsedTime.asMilliseconds() > 30)
		{
			if(isGameOn==true)
			{
				updateGame();
				gameClock.restart();
			}
			else
			{
				window.close();
				return 1;
			}
		}

		if(foodCounter.asSeconds() > 5.0)
		{
			M.spawnFood();
			foodClock.restart();
		}

		//Clear Window For Draw Next Loop
		window.clear();

		//Draw Map And Snake
		M.drawMap(window);
		S.drawSnake(window);

		//Display Loop
		window.display();
    }
	return 0;
}

int main()
{

	initGame();
	
	return 0;
}