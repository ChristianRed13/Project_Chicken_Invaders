#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<map>

#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

class GameFrame
{
private:

	//enemy
	float switchLevel;
	bool spawnModif;
	float spawnTime;
	float spawnTimeMax;


	int score;
	sf::Text scoreT;
	sf::Font scoreF;
	std::string playerName;
	std::string bulletType;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	Player* player;	
	std::vector<Projectile*> bullets;
	sf::Sound laserSound;
	sf::SoundBuffer laserSoundBuffer;

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> eggs;
	sf::Sound egg_crackSound;
	sf::SoundBuffer egg_crackSoundBuffer;




	std::map<std::string, sf::Texture*> textures;
	//Init
	void initSound();
	void initVariables();
	void initWindow();
	void initWorld();

	//Data 
	void setTextures();
	
public:
	//Constructors & Destructors
	GameFrame(std::string userName);
	virtual ~GameFrame();
	int getScore();

	//Getteri Setteri
	const bool getWindowIsOpen() const;
	std::string getPlayerName();

	//Functions
	void pollEvents();
	void levelMaker();
	void spawnEnemies();
	void gameOver();
	
	void updateEggs();
	void updateEnemies();
	void updateBullets();
	void updatePlayer();
	void update();


	void renderWorld();
	void renderPlayer();
	void renderBullets();
	void renderEggs();
	void renderEnemies();
	void render();

};

