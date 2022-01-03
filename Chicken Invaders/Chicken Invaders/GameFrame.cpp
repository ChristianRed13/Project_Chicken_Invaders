#include "GameFrame.h"
#include<string>


void GameFrame::initVariables()
{
	this->spawnTimeMax = 50.f;
	this->spawnTime = 0.f;
	this->window = nullptr;	
	this->score = 0;
}

void GameFrame::initWindow()
{

	this->videoMode.height = 900;
	this->videoMode.width = 1300;

	
	this->window = new sf::RenderWindow(this->videoMode, "Chicken invadors", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->player = new Player(this->playerName, this->window->getSize().x / 2, this->window->getSize().y);

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

	this->textures["GREEN_BULLET"] = new sf::Texture();
	this->textures["GREEN_BULLET"]->loadFromFile("Textures/green-double-bullet.png");

	this->textures["YELLOW_BULLET"] = new sf::Texture();
	this->textures["YELLOW_BULLET"]->loadFromFile("Textures/yellow-triple-bullet.png");

	this->textures["EGG"] = new sf::Texture();
	this->textures["EGG"]->loadFromFile("Textures/christmas-egg.png");

}

//Constructor & Destructor
GameFrame::GameFrame(std::string userName) 
{
	this->playerName = userName;
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
	for (auto& i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto& i : this->enemies)
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

//spaceship atack
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && this->player->canAtack())
		this->bullets.push_back(
			new Projectile(
				0.f,
				-1.f,
				this->player->getPos().x + this->player->getGlobalBounds().width / 2.f - this->textures["YELLOW_BULLET"]->getSize().x,
				this->player->getPos().y,
				1,
				this->textures["YELLOW_BULLET"]
                          )
							   );
//enemy spawner
	if (this->spawnTime == this->spawnTimeMax)
	{
		this->spawnTime = 0;
		
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x, 20.f));
		
	}
	else
		this->spawnTime++;

}

void GameFrame::updateEggs() {

	unsigned counter = 0;
	if (player->hp > 0)
		for (auto* egg : this->eggs)
		{
			egg->update();

			if (player->getGlobalBounds().intersects(egg->getGlobalBounds()))
			{
				player->setHp(egg->getDamage());
				delete this->eggs.at(counter);
				this->eggs.erase(this->eggs.begin() + counter);
				counter--;
			}

			counter++;
		}
	
}

void GameFrame::updateEnemies()
{
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		if (enemy->getHp() > 0)
		{
			enemy->update(this->window);
			if (enemy->canAtack())
				this->eggs.push_back(
				new Projectile(
					0.f,
					1.f,
					enemy->getPos().x + enemy->getGlobalBounds().width / 2.f - this->textures["EGG"]->getSize().x,
					enemy->getPos().y + enemy->getGlobalBounds().height,
					1,
					this->textures["EGG"]
				)
			);
		}
		else
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			counter--;
			score += 10;
		}

		counter++;
	}
}

std::string GameFrame::getPlayerName()
{
	return std::string(this->playerName);
}


//Functions
void GameFrame::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (!enemies.empty())
		{
			for (auto* enemy : this->enemies)
			{
				if (enemy->getGlobalBounds().intersects(bullet->getGlobalBounds()))
				{
					enemy->updateHp(bullet->getDamage());
					delete this->bullets.at(counter);
					this->bullets.erase(this->bullets.begin() + counter);
					counter--;
				}
			}
		}
		else if (bullet->getGlobalBounds().top + bullet->getGlobalBounds().height < 0.f)
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
	this->updateEggs();
	this->updatePlayer();
	this->updateEnemies();
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

int GameFrame::getScore()
{
	return this->score;
}

void GameFrame::renderBullets()
{
	for (auto* bullet : bullets)
	{
		bullet->render(this->window);
	}
}

void GameFrame::renderEnemies()
{
	for (auto* enemy : enemies)
	{
			enemy->render(this->window);
	}
}

void GameFrame::renderEggs()
{
	if (player->hp > 0)
		for (auto* egg : eggs)
		{
			egg->render(this->window);
		}
}

void GameFrame::render()
{

	this->window->clear();

	//draw stuff on window
	this->renderWorld();
	this->renderBullets();
	this->renderEnemies();
	this->renderEggs();
	this->renderPlayer();

	this->window->display();
}


