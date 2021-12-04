#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include<map>

#include "Player.h"
#include "Projectile.h"

class GameFrame
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	Player* player;	
	std::map<std::string, sf::Texture*> textures;
	std::vector<Projectile*> bullets;
	
	//Init
	void initVariables();
	void initWindow();
	void initWorld();

	//Data 
	void setTextures();
	
public:
	//Constructors & Destructors
	GameFrame();
	virtual ~GameFrame();

	//Getteri Setteri
	const bool getWindowIsOpen() const;

	//Functions
	void pollEvents();
	void menuEvents();

	void updateBullets();
	void updatePlayer();
	void update();


	void renderWorld();
	void renderPlayer();
	void renderBullets();
	void render();

};

