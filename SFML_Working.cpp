//Daniel Silva
//SFML Game:"Star Defender"
#include <SFML/Graphics.hpp>   //using namespace sf 
#include <time.h> 
#include "Header.h"
#include <iostream>
#include <math.h>


//Global Vars
float timer = 0.0f, delay = 0.1f;
int check = 1;
int numx = 1;
int numy = 1;
int score = 0;
int lives = 5;
int multi = 1;

//dimensions for window size and background 
int num_vertBox = 100, num_horzBox = 150;
int size = 16; 
int w = size * num_horzBox;  //background number of pixels in width 
int h = size * num_vertBox;    //background number of pixels in height 

//Structs for the objects in game: Gun and Ship
struct Gun
{
	int x, y;
}gun;
struct Ship
{
	int x, y;    
}ship;


void move() 
{
	//Makes game more difficult if score is greater than 5
	if (score > 5)
		multi=2;

	//Bounds: Bounces ship around the screen .
	//LEFT and RIGHT Bound
	if (ship.x > num_horzBox)
		numx = -1*multi;
	if (ship.x < 0)
		numx = 1*multi;
	//TOP and BOTTOM Bound
	if (ship.y > num_vertBox)
		numy = -1 * multi;
	if (ship.y < 0)
		numy = 1*multi;

	//Moves the ship around
	if ((check % 4 )== 1)
	{
		ship.y +=numy;
		ship.x +=numx;
	}
	check++;
	
	//Checks if Ship is clicked and respawns it. Also increments score 
	sf::IntRect r(ship.x*size, ship.y*size, timer*size,timer*size);
	float box = timer * timer * 2;
	if (r.contains(gun.x, gun.y)&& (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		ship.x = rand() % num_horzBox;
		ship.y = rand() % num_vertBox;
			//std::cout << "Im here";
		timer = 0;
			//std::cout << "in box!";
		score++;
	}	

	//Checks if ship is close to the screen and decrements lives
	if (timer > 10)
	{
		ship.x = rand() % num_horzBox;
		ship.y = rand() % num_vertBox;
		timer = 0;
		lives--;
	}
}



int main()

{

	//Setting pseudorandom time,   
	srand(time(0));

	//Window that we can play the game in  
	sf::RenderWindow window(sf::VideoMode(w, h), "Star Defender");

	//Textures load an image into the GPU Memory 
	sf::Texture t1, t2, t3, t4, explode;

	t1.loadFromFile("space3resize.png");
	t3.loadFromFile("spaceship_resize.png");
	t4.loadFromFile("gun.png");
	explode.loadFromFile("explode.png");



	sf::Sprite sprite1(t1);//Background
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);//Ship
	sf::Sprite sprite4(t4);//Gun
	sf::Sprite sprite5(explode);//Explosion



	//Initially place ship somewhere on screen 
	ship.x = 10;
	ship.y = 10;
	

	sf::Clock clock;

	while (window.isOpen())

	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something 
		sf::Event e;

		//Check when the window is closed 
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window 
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Gets mouse position and sets gun to same position.
		sf::Vector2i position = sf::Mouse::getPosition(window);
		gun.x = position.x;
		gun.y = position.y;
	
		if (timer > delay)
		{
			move();    
		}
		
		//Draw in window
		window.clear();    //clear the window so new frame can be drawn in 

		//Draws Background
		sprite1.setPosition(0, 0);
		window.draw(sprite1);

		//Draws the Gun at the mouse position 
		sprite4.setPosition(gun.x, gun.y);
		window.draw(sprite4);

		//Draws the Ship and scales it to the timer to make it look like its getting closer
		int i = (int)timer;
		sprite3.setScale(timer, timer);
		sprite3.setPosition(ship.x * size, ship.y * size);
		window.draw(sprite3);
		if (timer > 8)
		{
			sprite5.setScale(timer*2, timer*2);
			sprite5.setPosition(ship.x* size, ship.y* size);
			window.draw(sprite5);
		}
			
		std::cout << timer<<"\n";

		// Declare and load a font
		sf::Font font;
		font.loadFromFile("Arial.ttf");
		
		// Create a text: the points score and the number of lives 
		sf::Text points,liveNum;
		points.setFont(font);
		points.setString("Score: "+std::to_string(score));
		points.setCharacterSize(30);
		points.setStyle(sf::Text::Bold);
		points.setFillColor(sf::Color::Red);
		points.setPosition( 0,0);
		window.draw(points);
		liveNum.setFont(font);
		liveNum.setString("Lives: " + std::to_string(lives));
		liveNum.setCharacterSize(30);
		liveNum.setStyle(sf::Text::Bold);
		liveNum.setFillColor(sf::Color::Red);
		liveNum.setPosition(16*size, 0);
		window.draw(liveNum);

		//Cut to the Game Over display 
		if (lives < 1)
		{
			sprite1.setPosition(0, 0);
			window.draw(sprite1);
			points.setCharacterSize(40);
			points.setPosition(70*size, 30*size);
			window.draw(points);
			sf::Text go("Game Over", font);
			go.setCharacterSize(100);
			go.setStyle(sf::Text::Bold);
			go.setFillColor(sf::Color::Red);
			go.setPosition(58 * size, 16*size);
			window.draw(go);
			sf::Text playA("Press Space to Play Again", font);
			playA.setCharacterSize(60);
			playA.setStyle(sf::Text::Bold);
			playA.setFillColor(sf::Color::Red);
			playA.setPosition(52 * size, 45 * size);
			window.draw(playA);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				score = 0;
				lives = 5; 
				timer = 0;
			}

		}
		
		//Show everything we have drawn on the screen 
		window.display();
	}
	return 0;
}