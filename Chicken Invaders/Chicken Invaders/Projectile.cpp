#include "Projectile.h"

Projectile::Projectile()
{
	this->initVariables();
}

Projectile::Projectile(float direction_x, float direction_y, float origin_x, float origin_y, int damage, sf::Texture* texture)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(2.f, 2.f);

	this->damage = damage;
	
	this->direction.x = direction_x;
	this->direction.y = direction_y;
	this->shape.setPosition(origin_x, origin_y);
	this->initVariables();
	
}

Projectile::~Projectile()
{
	
}

void Projectile::setDamage(int dmg)
{
	this->damage = dmg;
}


void Projectile::initVariables()
{
	this->movementSpeed = 10.f;
}

sf::FloatRect Projectile::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

sf::Vector2f Projectile::getShapePosition()
{
	return this->shape.getPosition();
}

int Projectile::getDamage()
{
	return this->damage;
}

void Projectile::update()
{
		this->shape.move(this->movementSpeed * this->direction);

}

void Projectile::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
}



