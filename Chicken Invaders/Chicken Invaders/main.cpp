#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "GameFrame.h"
#include "MainMenu.h"

using namespace sf;

int main()
{
	RenderWindow MENU(VideoMode(960, 720), "Main Menu", Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);
	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return) {
					RenderWindow OPTIONS(VideoMode(960, 720), "OPTIONS");
					RenderWindow ABOUT(VideoMode(960, 720), "ABOUT");
					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						GameFrame gameFrame;
						while (gameFrame.getWindowIsOpen())
						{
							gameFrame.update();

							OPTIONS.clear();
							ABOUT.close();
							gameFrame.render();
						}
					}
					if (x == 1)
						while (OPTIONS.isOpen())
						{
							Event aevent;
							while (OPTIONS.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									OPTIONS.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										OPTIONS.close();
									}
								}
							}
					
							OPTIONS.clear();
							ABOUT.close();
							OPTIONS.display();
						}
					if (x == 2)
						while (ABOUT.isOpen())
						{
							Event aevent;
							while (ABOUT.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									ABOUT.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										ABOUT.close();
									}
								}

							}
							
							OPTIONS.clear();
							ABOUT.close();
							OPTIONS.display();

						}
					if (x == 3)
						MENU.close();
					break;
				}
			}
		}
		MENU.clear();
		mainMenu.draw(MENU);
		MENU.display();

	}

	return 0;
}
