#include "Player.h"
#include <string>
#include <SFML/Window.hpp>



void Player::initVariables()
{
	this->hp = maxHP;

	this->atackCooldownMax = 10.f;
	this->atackCooldown = this->atackCooldownMax;

	this->animationCooldownMax = 20;
	this->animationCooldown = this->animationCooldownMax;

	this->movementSpeed = 10.f;
}

void Player::initTexture() {
	if (!this->texture.loadFromFile("Textures/spaceship-viollet.png"))
		std::cout << "Texture Ship not found!";
	
	if (!this->healthTexture.loadFromFile("Textures/Healthbar-4.png"))
		std::cout << "Texture Health not found!";

	if (!this->powerTexture.loadFromFile("Textures/Powerup-0.png"))
		std::cout << "Texture Power not found!";

	
		
}

void Player::initShape()
{
	this->shape.setTexture(this->texture);
	this->shape.setScale(5.f, 5.f);

	this->healthShape.setTexture(this->healthTexture);
	this->healthShape.setScale(5.f, 5.f);

	this->powerShape.setTexture(this->powerTexture);
	this->powerShape.setScale(5.f, 5.f);
}

Player::Player() {
	this->initVariables();
	this->initTexture();
	this->initShape();
}
Player::Player(const Player& player)
{
	this->shape.setPosition(player.shape.getPosition());
	this->name = player.name;
	this->initVariables();
	this->initTexture();
	this->initShape();
};

Player::Player(std::string name, float x, float y)
{
	this->initVariables();
	this->initTexture();
	this->initShape();
	this->shape.setPosition(x - this->shape.getGlobalBounds().width / 2, y);
	this->healthShape.setPosition(0, 0);
	this->powerShape.setPosition(0, 40);
	this->name = name;
}

Player::~Player()
{
}

const sf::Vector2f Player::getPos() const 
{
	return this->shape.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const bool Player::canAtack()
{
	if (this->atackCooldown >= this->atackCooldownMax)
	{
		this->atackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAtackCooldown()
{
	if (this->atackCooldown < this->atackCooldownMax)
		this->atackCooldown += 1.f;
}

void Player::updateAnimationCooldown()
{
	if (this->animationCooldown < this->animationCooldownMax)
		this->animationCooldown += 1;
	else
		this->animationCooldown = 0;
}

void Player::updateAnimationTexture()
{
	
	switch (this->animationCooldown)
	{
	case 0:
		this->texture.loadFromFile("Textures/spaceship-viollet.png");
		break;
	case 5:
		this->texture.loadFromFile("Textures/space-ship-2.png");
		break;
	case 10:
		this->texture.loadFromFile("Textures/space-ship-3.png");
		break;
	case 15:
		this->texture.loadFromFile("Textures/space-ship-4.png");
		break;
	}
		
	
}

void Player::updateWindowBounds(const sf::RenderTarget* target)
{
	//window bounds:
	if (this->shape.getPosition().x < 0)
			this->shape.setPosition(0, shape.getPosition().y);
	 if (this->shape.getPosition().y < 0)
			this->shape.setPosition(shape.getPosition().x, 0);
	 if (this->shape.getPosition().x + this->shape.getGlobalBounds().width > target->getSize().x)
			this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, shape.getPosition().y);
	 if (this->shape.getPosition().y + this->shape.getGlobalBounds().height > target->getSize().y)
			this->shape.setPosition(shape.getPosition().x, target->getSize().y - this->shape.getGlobalBounds().height);

}
//  |y
//------x
//  |
//

void Player::updateInput()
{
	//movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->shape.move(-this->movementSpeed, 0.f);
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->shape.move(this->movementSpeed, 0.f);
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->shape.move(0.f, -this->movementSpeed);
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->shape.move(0.f, this->movementSpeed);

	
}

void Player::updateHealthbar()
{

	switch (hp)
	{
	case 0: this->healthTexture.loadFromFile("Textures/Healthbar-0.png");
		break;
	case 1: this->healthTexture.loadFromFile("Textures/Healthbar-1.png");
		break;
	case 2: this->healthTexture.loadFromFile("Textures/Healthbar-2.png");
		break;
	case 3: this->healthTexture.loadFromFile("Textures/Healthbar-3.png");
		break;
	case 4: this->healthTexture.loadFromFile("Textures/Healthbar-4.png");
		break;
	}
}

void Player::setHp(int dmg)
{
	this->hp -= dmg;
}

void Player::updatePowerup()
{
	//powerup cooldown 

}

void Player::update(const sf::RenderTarget* target)
{
	this->updateAnimationTexture();
	this->updateAnimationCooldown();
	this->updateAtackCooldown();
	this->updateWindowBounds(target);
	this->updateInput();
	this->updatePowerup();
	this->updateHealthbar();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->healthShape);
	target->draw(this->powerShape);
}



