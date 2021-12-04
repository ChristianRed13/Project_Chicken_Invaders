#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Enemy
{
private:
	//variabile



public:
	//blueprint functii
	void update(sf::RenderTarget* window);
	void render(sf::RenderTarget* window);
};

