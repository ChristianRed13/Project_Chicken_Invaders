#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>

class NewGame
{
private:
	int screenWidth;
	int screenHeight;

	int maxCharacters;

	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	std::string playerName;

	sf::Text titleText;

	std::string playerInput;
	sf::Text playerOutput;

	sf::RenderWindow* window;
	sf::Event event;


	void initVariables();
	void initWindow();
	void initWorld();


public:
	NewGame(int width, int height);
	~NewGame();

	const bool getWindowIsOpen() const;

	void pollEvents();
	sf::Event getEvent();

	void updateTextPozition();
	void update();
	std::string getUser();
	bool isUserFieldCompleted();

	void render();


};

