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
	
	int damage;

	float origin_x;
	float origin_y;
	sf::Vector2f direction;
	float movementSpeed;

	sf::Sprite shape;

public:
	Projectile();
	Projectile(float direction_x, float direction_y, float origin_x, float origin_y, int damage, sf::Texture* texture);
	virtual ~Projectile();

	void setDamage(int dmg);


	void initVariables();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getShapePosition();

	int getDamage();

	void update();
	void render(sf::RenderWindow* window);

};

#endif 
