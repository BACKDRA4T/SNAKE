class Snake {
	int direction, head;
	bool foodEaten;
	std::string facing; 
	std::deque<sf::RectangleShape> snakeBody;
public:
	sf::RectangleShape createSeg();
	void setDirection(const int d) {direction = d;}; // "1" == UP, "2" == DOWN, "3" == LEFT, "4" == RIGHT 
	void createSnake(int);
	void shiftSeg();
	void drawSnake(sf::RenderWindow &window);
	void eatFood() { foodEaten = true; };
	sf::FloatRect getSnakeHeadPos();
	bool checkSnakeCollision(const std::vector<sf::RectangleShape> &, const int, const int);
	friend class Map;
};

sf::RectangleShape Snake::createSeg()
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(18, 18));
	rectangle.setFillColor(sf::Color::Green);
	sf::Color outlineColour(145, 145, 145);
	rectangle.setOutlineColor(outlineColour);
	rectangle.setOutlineThickness(2);

	return rectangle;
}

void Snake::createSnake(const int length)
{
	//Set Head Int
	head = 0;

	//Create Body Tiles
	for(int i=0; i <= length; ++i)
	{
		sf::RectangleShape rectangle = createSeg();
		if(i==0)
		{
			rectangle.setPosition(400,300);
		}
		else
		{
			rectangle.setPosition(400,snakeBody[i-1].getPosition().y+20);
		}
		snakeBody.push_back(rectangle);
	}
}

void Snake::shiftSeg()
{

	//Check if food eaten and if so leave last segment else take segment off
	if(foodEaten == true)
	{
		foodEaten = false;
	}
	else
	{
		snakeBody.pop_back();
	}

	//Set direction
	sf::RectangleShape rectangle = createSeg();

	if(direction == 1) //UP
	{
		if(facing == "UP" || facing == "LEFT" || facing == "RIGHT" ) // Go new direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x,snakeBody[head].getPosition().y-20);
			snakeBody.push_front(rectangle);
			facing = "UP";
		}
		else //Keep going opposite direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x,snakeBody[head].getPosition().y+20);
			snakeBody.push_front(rectangle);
			facing = "DOWN";
		}
	}
	else if(direction == 2) //DOWN
	{
		if(facing == "DOWN" ||facing == "LEFT" || facing == "RIGHT") // Go new direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x,snakeBody[head].getPosition().y+20);
			snakeBody.push_front(rectangle);
			facing = "DOWN";
		}
		else //Keep going opposite direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x,snakeBody[head].getPosition().y-20);
			snakeBody.push_front(rectangle);
			facing = "UP";
		}
	}
	else if(direction == 3) //LEFT
	{
		if(facing == "UP" || facing == "DOWN" || facing == "LEFT") // Go new direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x-20,snakeBody[head].getPosition().y);
			snakeBody.push_front(rectangle);
			facing = "LEFT";
		}
		else //Keep going opposite direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x+20,snakeBody[head].getPosition().y);
			snakeBody.push_front(rectangle);
			facing = "RIGHT";
		}
	}
	else if(direction == 4) //RIGHT
	{
		if(facing == "UP" || facing == "DOWN"|| facing == "RIGHT") // Go new direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x+20,snakeBody[head].getPosition().y);
			snakeBody.push_front(rectangle);
			facing = "RIGHT";
		}
		else //Keep going opposite direction
		{
			rectangle.setPosition(snakeBody[head].getPosition().x-20,snakeBody[head].getPosition().y);
			snakeBody.push_front(rectangle);
			facing = "LEFT";
		}
	}
	else // FIRST START GAME (START UP)
	{
		head = 0;
		rectangle.setPosition(snakeBody[head].getPosition().x, snakeBody[head].getPosition().y-20);
		snakeBody.push_front(rectangle);
		facing = "UP";
	}
}

void Snake::drawSnake(sf::RenderWindow &window)
{	
	int snakeSize = snakeBody.size();
	for(int i=0; i < snakeSize; ++i)
	{
		window.draw(snakeBody[i]);
	}
}

sf::FloatRect Snake::getSnakeHeadPos()
{
	return snakeBody[head].getGlobalBounds();
}

bool Snake::checkSnakeCollision(const std::vector<sf::RectangleShape> & map, int mapWidth, int mapHeight) // FIX
{
	//Collides with Body
	for(int x = 1; x < snakeBody.size(); ++x)
	{
		if(snakeBody[0].getGlobalBounds() == snakeBody[x].getGlobalBounds())
		{
			return true;
		}

	}

	//Collides with Edge Of Map
	if(snakeBody[0].getPosition().x < map[0].getPosition().x || snakeBody[0].getPosition().x > map[mapWidth-1].getPosition().x
		|| snakeBody[0].getPosition().y < map[0].getPosition().y || snakeBody[0].getPosition().y > map[mapWidth*mapHeight-1].getPosition().y)
	{
		return true;
	}

	return false;
}