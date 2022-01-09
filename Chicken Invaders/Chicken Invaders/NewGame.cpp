#include "NewGame.h"

void NewGame::initVariables()
{

	this->maxCharacters = 15;
	this->font.loadFromFile("Fonts/PressStart2P-Regular.ttf");
	this->playerOutput = sf::Text("_", this->font);
	this->playerOutput.setFillColor(sf::Color::White);
	this->playerOutput.setCharacterSize(60);

	this->titleText = sf::Text("Enter name:", this->font);
	this->titleText.setFillColor(sf::Color::White);
	this->titleText.setCharacterSize(70);
	this->titleText.setOutlineColor(sf::Color::Black);
			
}

void NewGame::initWindow()
{

	this->window = new sf::RenderWindow(sf::VideoMode(this->screenWidth, this->screenHeight), "Chicken invadors", sf::Style::Default);
	this->window->setFramerateLimit(60);
	this->background.setScale(this->window->getSize().x / background.getLocalBounds().width,
	this->window->getSize().y / background.getLocalBounds().height);

	this->playerOutput.setPosition(this->window->getSize().x / 2 + this->playerOutput.getLocalBounds().width / 2, this->window->getSize().y / 3);
	this->titleText.setPosition(this->window->getSize().x / 2 - this->titleText.getLocalBounds().width / 2, this->window->getSize().y / 5);
}

void NewGame::initWorld()
{
	if (!this->backgroundTexture.loadFromFile("Textures/Back1.jpg"))
	{
		std::cout << "ERROR::GAME_Login::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	
	this->background.setTexture(this->backgroundTexture);
}

NewGame::NewGame(int width, int height)
{
    this->screenHeight = height;
    this->screenWidth = width;
	this->initVariables();
	this->initWorld();
	this->initWindow();
	
	
	
}

NewGame::~NewGame()
{
	delete this->window;
}

const bool NewGame::getWindowIsOpen() const
{
    return this->window->isOpen();
}

void NewGame::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::TextEntered:
				if (std::isprint(event.text.unicode) && this->playerInput.size()<this->maxCharacters)
					this->playerInput += this->event.text.unicode;
			break;

		case sf::Event::KeyPressed:
	

			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			
				if (this->event.key.code == sf::Keyboard::Enter)
					if (!playerInput.empty())
						this->window->close();

			if (event.key.code == sf::Keyboard::BackSpace) 
				if (!playerInput.empty())
					this->playerInput.pop_back();

			break;
		}
    }
}

sf::Event NewGame::getEvent()
{
	return this->event;
}

void NewGame::updateTextPozition()
{
	if(this->playerOutput.getString().getSize() < this->playerInput.size())
		this->playerOutput.setPosition(this->playerOutput.getPosition().x -((this->playerInput.size() - this->playerOutput.getString().getSize()) * this->playerOutput.getCharacterSize()/1.8), this->playerOutput.getPosition().y);
	if(this->playerOutput.getString().getSize() > this->playerInput.size())
		this->playerOutput.setPosition(this->playerOutput.getPosition().x + ((this->playerOutput.getString().getSize() - this->playerInput.size()) * this->playerOutput.getCharacterSize()/1.8 ), this->playerOutput.getPosition().y);

}

void NewGame::update()
{
	this->pollEvents();
	this->updateTextPozition();
	this->playerOutput.setString(this->playerInput);

}

std::string NewGame::getUser()
{
	return this->playerInput;
}

bool NewGame::isUserFieldCompleted()
{
	return this->playerInput.empty();
}

void NewGame::render()
{
	this->window->clear();

	this->window->draw(this->background);
	this->window->draw(this->titleText);
	this->window->draw(this->playerOutput);

	this->window->display();
}
