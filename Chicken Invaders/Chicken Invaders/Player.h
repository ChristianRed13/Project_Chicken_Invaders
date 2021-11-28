#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	float atackCooldownMax;
	float atackCooldown;

	std::string name;
	sf::Texture texture;
	sf::Sprite shape;
	float movementSpeed;

	void initTexture();
	void initVariables();
	void initShape();

public:

	Player(std::string name , float x , float y );
	Player();
	Player(const Player& player);
	virtual ~Player();
	
	const sf::Vector2f getPos() const;
	const sf::FloatRect getGlobalBounds() const;

	const bool canAtack();
	void updateAtackCooldown();

	void updateWindowBounds(const sf::RenderTarget* target);
	void updateInput();
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

