#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
class Animation
{
private:

	sf::Texture* animation;
	sf::Sprite* shape;
	
	sf::Vector2i picture = sf::Vector2i(1, 0);
	const float numberOfAnimations;
	float animationSize;

	float animationCooldown;
	float maxAnimationCooldown;




public:

};

