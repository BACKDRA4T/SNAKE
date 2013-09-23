class Snake;

class Map {
	std::vector<sf::RectangleShape> tiles;
	sf::RectangleShape food;
	int widthOfMap, heightOfMap, numTiles;
	bool foodSpawned;
public:
	void setSizeOfMap(const int, const int);
	void createTiles();
	void drawMap(sf::RenderWindow &);
	std::vector<sf::RectangleShape> & accessMap() {return tiles;}; //Return Const Safe Pointer to Tiles
	void spawnFood();
	bool offMap();
	sf::FloatRect getFoodPos();
};

void Map::setSizeOfMap(const int x, const int y)
{
	widthOfMap = (x/20);
	heightOfMap = (y/20);
	numTiles = (widthOfMap*heightOfMap);
}

void Map::createTiles()
{
	//Create Tiles
	int col = 0;
	while(col < heightOfMap)
	{
		for(int row = 0; row != widthOfMap; ++row)
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(20, 20));
			rectangle.setFillColor(sf::Color::Black);
			sf::Color outlineColour(0, 0, 0);
			rectangle.setOutlineColor(outlineColour);
			rectangle.setOutlineThickness(2);	
			if(tiles.size() == 0 || row == 0)
			{
				rectangle.setPosition(0,col*20);
			}
			else
			{
				rectangle.setPosition(tiles[row-1].getPosition().x+20,col*20);
			}
			tiles.push_back(rectangle);
		}
		++col;
	}
}

void Map::drawMap(sf::RenderWindow &window)
{
	//Draw Tiles
	for(unsigned int n= 0; n < tiles.size(); ++n)
	{
		window.draw(tiles[n]);
	}
	//Draw Food
	window.draw(food);
}

void Map::spawnFood() // Fix so doesn't spawn on snake
{
	//Generate Random Numbers For Grid Pos For Food
	srand(time(NULL));
	int randomTile = rand() % numTiles;

	if(foodSpawned != true)
	{
		food.setSize(sf::Vector2f(18, 18));
		food.setFillColor(sf::Color::Red);
		sf::Color outlineColour(145, 145, 145);
		food.setOutlineColor(outlineColour);
		food.setOutlineThickness(2);
		food.setPosition(tiles[randomTile].getPosition().x, tiles[randomTile].getPosition().y);
		foodSpawned = true;
	}
	else
	{
		food.setPosition(tiles[randomTile].getPosition().x, tiles[randomTile].getPosition().y);
	}
}

sf::FloatRect Map::getFoodPos()
{
	return food.getGlobalBounds();
}
