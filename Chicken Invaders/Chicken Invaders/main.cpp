#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "GameFrame.h"

using namespace sf;

int main()
{
	GameFrame gameFrame;

	while (gameFrame.getWindowIsOpen())
	{
		gameFrame.update();
		gameFrame.render();
	}

	return 0;
}
