#include "Player.h"



void Player::initVariables()
{
	this->atackCooldown = 0.f;
	this->atackCooldownMax = 10;
	this->movementSpeed = this->atackCooldownMax;
}

void Player::initTexture() {
	if (!this->texture.loadFromFile("Textures/spaceship-viollet.png"))
		std::cout << "Texture not found!";
		
}

void Player::initShape()
{
	this->shape.setTexture(this->texture);
	this->shape.setScale(5.f, 5.f);
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
		this->atackCooldown += 0.5f;
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

void Player::update(const sf::RenderTarget* target)
{
	this->updateAtackCooldown();
	this->updateWindowBounds(target);
	this->updateInput();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}



