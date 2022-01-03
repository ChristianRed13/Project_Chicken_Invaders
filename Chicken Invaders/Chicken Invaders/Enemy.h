#ifndef ENEMY_H
#define ENEMY_H

#include<iostream>
#include"Projectile.h"
class sf::RenderTarget;

class Enemy
{
private:
	//variabile
	bool move;
	int hp;
	float atackCooldown;
	float maxAtackCooldown;

	int animationCooldownMax;
	int animationCooldown;

	int numberOfAnimations;
	sf::Vector2i animationSize;


	sf::Texture texture;
	sf::Sprite shape;
	

	void initTexture();
	void initVariables();
	void initShape();


public:
	Enemy(float position_x, float position_y);
	~Enemy();

	//global position
	const sf::Vector2f getPos() const;
	const sf::FloatRect getGlobalBounds() const;

	//getters & setters
	void setHp(int hp);
	int getHp();

	//atack
	bool canAtack();
	void resetAtack();

	//animations
	void updateAnimationCooldown();
	void updateAnimationTexture();

	//movement
	void updateMovementDirection(const sf::RenderWindow* target);
	void updateWindowBounds();
	void updateHp(int dmg);

	//base functions
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
};

#endif 