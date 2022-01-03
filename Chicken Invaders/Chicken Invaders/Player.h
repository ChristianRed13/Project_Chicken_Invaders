#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Projectile.h"
//BETTER FOR COMPILER
class string;
class sf::RenderTarget;

class Player
{
private:
	int maxHP = 4;
	

	float atackCooldownMax;
	float atackCooldown;

	int animationCooldownMax;
	int animationCooldown;

	sf::Texture powerTexture;
	sf::Sprite powerShape;

	sf::Texture healthTexture;
	sf::Sprite healthShape;

	std::string name;
	sf::Texture texture;
	sf::Sprite shape;
	float movementSpeed;

	void initTexture();
	void initVariables();
	void initShape();

public:
	int hp;
	Player(std::string name , float x , float y );
	Player();
	Player(const Player& player);
	virtual ~Player();
	
	const sf::Vector2f getPos() const;
	const sf::FloatRect getGlobalBounds() const;

	void setHp(int dmg);

	const bool canAtack();
	void updateAtackCooldown();
	void updateAnimationCooldown();
	void updateAnimationTexture();

	void updateWindowBounds(const sf::RenderTarget* target);
	void updateInput();
	void updateHealthbar();
	void updatePowerup();
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

