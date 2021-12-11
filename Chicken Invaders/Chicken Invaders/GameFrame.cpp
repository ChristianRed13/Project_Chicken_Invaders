#include "GameFrame.h"


void GameFrame::initVariables()
{
	this->window = nullptr;	
	
}

void GameFrame::initWindow()
{

	this->videoMode.height = 900;
	this->videoMode.width = 1300;

	this->window = new sf::RenderWindow(this->videoMode, "Chicken invadors", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->player = new Player("Chrboss", this->window->getSize().x / 2, this->window->getSize().y);

	this->background.setScale(this->window->getSize().x / background.getLocalBounds().width,
		this->window->getSize().y / background.getLocalBounds().height);

}


void GameFrame::initWorld()
{
	if (!this->backgroundTexture.loadFromFile("Textures/Background.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->background.setTexture(this->backgroundTexture);


}


void GameFrame::setTextures()
{
	this->textures["BLUE_BULLET"] = new sf::Texture();
	this->textures["BLUE_BULLET"]->loadFromFile("Textures/bullet-blue.png");

	this->textures["RED_BULLET"] = new sf::Texture();
	this->textures["RED_BULLET"]->loadFromFile("Textures/bullet-red.png");

	this->textures["VIOLLET_BULLET"] = new sf::Texture();
	this->textures["VIOLLET_BULLET"]->loadFromFile("Textures/bullet-viollet.png");	

}

//Constructor & Destructor
GameFrame::GameFrame() 
{

	this->initWorld();//background
	this->setTextures();//seteaza texturile
	this->initVariables();//
	this->initWindow();
	
}

GameFrame::~GameFrame()
{
	delete this->window;
	delete this->player;
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
}

//Getteri Setteri
const bool GameFrame::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void GameFrame::pollEvents()
{
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
				this->window->close();
			break;
		}
	}

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && this->player->canAtack())
		this->bullets.push_back(
			new Projectile(
				0.f,
				-1.f,
				this->player->getPos().x + this->player->getGlobalBounds().width / 2.f - 10.f,
				this->player->getPos().y,
				this->textures["BLUE_BULLET"]
                          )
							   );

}


//Functions
void GameFrame::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getGlobalBounds().top + bullet->getGlobalBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			counter--;
		//	std::cout<<this->bullets.size()<< '\n';
		}

		counter++;
	}
}



void GameFrame::updatePlayer()
{
	this->player->update(this->window);
}

void GameFrame::update()
{
	this->pollEvents();
	this->updatePlayer();
	this->updateBullets();

}

void GameFrame::renderWorld()
{
	this->window->draw(this->background);
}


void GameFrame::renderPlayer()
{
	this->player->render(this->window);
}

void GameFrame::renderBullets()
{
	for (auto* bullet : bullets)
	{
		bullet->render(this->window);
	}
}


void GameFrame::render()
{

	this->window->clear();

	//draw stuff on window
	this->renderWorld();
	this->renderBullets();
	this->renderPlayer();
	



	this->window->display();
}


