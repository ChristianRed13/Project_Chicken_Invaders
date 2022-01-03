#include "Enemy.h"
#include <SFML/Window.hpp>

void Enemy::initTexture()
{
	if (!this->texture.loadFromFile("Textures/enemy-animation.png"))
		std::cout << "Texture Enemy not found!";

}

void Enemy::initVariables()
{
	this->animationSize.x = 175;
	this->animationSize.y = 190;
	this->animationCooldownMax = 20;
	this->animationCooldown = 0;
	this->move = true;
	this->hp = 1;
	this->maxAtackCooldown = 200.f;
	this->atackCooldown = this->maxAtackCooldown / 2;
}

void Enemy::initShape()
{
	this->shape.setTexture(this->texture);
	this->shape.setTextureRect(sf::IntRect(0, 0, this->animationSize.x, this->animationSize.y));	
}

Enemy::Enemy(float position_x, float position_y)
{
	
	this->initVariables();
	this->initTexture();
	this->initShape();
	this->shape.setPosition(position_x, position_y);
	
}

Enemy::~Enemy()
{	
}

const sf::Vector2f Enemy::getPos() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Enemy::setHp(int hp)
{
	this->hp = hp;
}

int Enemy::getHp()
{
	return this->hp;
}

void Enemy::updateAnimationCooldown()
{
	if (this->animationCooldown < this->animationCooldownMax)
		this->animationCooldown += 1;
	else
		this->animationCooldown = 0;
}

void Enemy::updateAnimationTexture()
{
	switch (this->animationCooldown)
	{
	case 0:
		this->shape.setTextureRect(sf::IntRect(this->animationSize.x * 0, 0, this->animationSize.x, this->animationSize.y));
		break;
	case 5:
		this->shape.setTextureRect(sf::IntRect(this->animationSize.x * 1, 0, this->animationSize.x, this->animationSize.y));
		break;
	case 10:
		this->shape.setTextureRect(sf::IntRect(this->animationSize.x * 2, 0, this->animationSize.x, this->animationSize.y));
		break;
	case 15:
		this->shape.setTextureRect(sf::IntRect(this->animationSize.x * 3, 0, this->animationSize.x, this->animationSize.y));
		break;
	}

}

 bool Enemy::canAtack()
{
	 if (this->atackCooldown == 0)
		 return true;
	 return false;
}

void Enemy::resetAtack()
{
	if (this->atackCooldown < this->maxAtackCooldown)
		this->atackCooldown = this->atackCooldown + 1.f;
	else
		this->atackCooldown = 0.f;
}

void Enemy::updateMovementDirection(const sf::RenderWindow* target)
{
	if (this->shape.getPosition().x + this->shape.getGlobalBounds().width > target->getSize().x)
		this->move = false;
	else if (this->shape.getPosition().x < target->getPosition().x)
		this->move = true;
}

void Enemy::updateWindowBounds()
{
	if (this->move)
		this->shape.move(5.f, 0.f);
	if (!this->move)
		this->shape.move(-5.f, 0.f);
	
}

void Enemy::updateHp(int dmg)
{
		this->hp -= dmg;
}

void Enemy::update(sf::RenderWindow* window)
{
//	this->updateInput();
	this->updateAnimationCooldown();
	this->updateAnimationTexture();
	

	this->updateMovementDirection(window);
	this->updateWindowBounds();

	this->resetAtack();
}

void Enemy::render(sf::RenderWindow* window)
{
		window->draw(this->shape);

	//window->draw(this->egg);
}
