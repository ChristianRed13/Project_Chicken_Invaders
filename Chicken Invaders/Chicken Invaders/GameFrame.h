#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class GameFrame
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::Texture texture;
	sf::Sprite sprite;
	

	void initVariables();
	void initWindow();
	
public:
	//Constructors & Destructors
	GameFrame();
	virtual ~GameFrame();

	//Getteri Setteri
	const bool getWindowIsOpen() const;

	//Functions
	void pollEvents();
	void update();
	void render();
};

