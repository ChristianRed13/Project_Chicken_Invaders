#include "GameFrame.h"

void GameFrame::initVariables()
{
	window = nullptr;
	texture.loadFromFile("bullet-red.png");
	sprite.setTexture(this->texture);
	//sprite.setScale(5, 5);
}

void GameFrame::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1000;

	this->window = new sf::RenderWindow(this->videoMode, "Chicken invadors", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
}

//Constructor & Destructor
GameFrame::GameFrame() 
{
	initVariables();
	initWindow();
}

GameFrame::~GameFrame()
{
	delete window;
}

//Getteri Setteri
const bool GameFrame::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void GameFrame::pollEvents()
{
	float movementSpeed = 10.f;
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			//ALL KEYBOARD EVENTS HERE:
			//EXIT FULLSCREEN
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->create(this->videoMode, "Chicken invadors",
					sf::Style::Titlebar |
					sf::Style::Close);
				this->window->setFramerateLimit(60);
			}
		/*	//ENTER FULLSCREEN
			if (this->event.key.code == sf::Keyboard::LShift)
				this->window->create(this->videoMode, "Chicken invadors", sf::Style::Fullscreen);

			//RIGHT BORDER
			if ((this->event.key.code == sf::Keyboard::D || this->event.key.code == sf::Keyboard::Right)
				&& this->sprite.getPosition().x + this->sprite.getGlobalBounds().width <= this->window->getSize().x
				)
				this->sprite.move(10.f, 0.f);


			//DOWN BORDER
			if ((this->event.key.code == sf::Keyboard::S || this->event.key.code == sf::Keyboard::Down)
				&& this->sprite.getPosition().y + this->sprite.getGlobalBounds().height <= this->window->getSize().y
				)
				this->sprite.move(0.f, 10.f);

			//LEFT BORDER
			if ((this->event.key.code == sf::Keyboard::A || this->event.key.code == sf::Keyboard::Left)
				&& this->sprite.getPosition().x >= 0
				)
				this->sprite.move(-10.f, 0.f);
			//UP BORDER
			if ((this->event.key.code == sf::Keyboard::W || this->event.key.code == sf::Keyboard::Up)
				&& this->sprite.getPosition().y >= 0
				)
				this->sprite.move(0.f, -10.f);
				*/
			break;
		}
	}
	//BETER
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->sprite.move(-movementSpeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->sprite.move(movementSpeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->sprite.move(0.f, -movementSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->sprite.move(0.f, movementSpeed);

	//Conditii de border

	if (this->sprite.getPosition().x <= 0)
		this->sprite.setPosition(0, sprite.getPosition().y);
	if (this->sprite.getPosition().y <= 0)
		this->sprite.setPosition(sprite.getPosition().x, 0);
	if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width >= this->window->getSize().x)
		this->sprite.setPosition(this->window->getSize().x - this->sprite.getGlobalBounds().width, sprite.getPosition().y);
	if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height >= this->window->getSize().y)
		this->sprite.setPosition(sprite.getPosition().x, this->window->getSize().y - this->sprite.getGlobalBounds().height);
}

//Functions
void GameFrame::update()
{
	this->pollEvents();
}

void GameFrame::render()
{

	this->window->clear();

	//draw stuff on window
	this->window->draw(sprite);

	this->window->display();
} 
