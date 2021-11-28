#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


class Projectile
{
private:
	
	float origin_x;
	float origin_y;
	sf::Vector2f direction;
	float movementSpeed;

	sf::Sprite shape;

public:
	Projectile();
	Projectile(float direction_x, float direction_y, float origin_x, float origin_y, sf::Texture* texture);
	virtual ~Projectile();


	void initVariables();
	sf::FloatRect getGlobalBounds();

	void update();
	void render(sf::RenderWindow* window);

};

#endif 
