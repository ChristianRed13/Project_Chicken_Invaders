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
	MENU.setFramerateLimit(60);
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
				if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return) {
					//RenderWindow help(VideoMode(960, 720), "HELP");
					//RenderWindow about(VideoMode(960, 720), "ABOUT");
					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						MENU.close();
						GameFrame gameFrame;
						while (gameFrame.getWindowIsOpen())
						{
							gameFrame.update();

							//help.clear();
							//about.close();
							gameFrame.render();
						}
						MENU.create(VideoMode(960, 720), "Main Menu", Style::Default);
						MENU.setFramerateLimit(60);
					}
					if (x == 1)
					{
						MENU.close();
						RenderWindow help(VideoMode(960, 720), "HELP");
						Texture help_png;
						help_png.loadFromFile("Textures/help_menu.png");

						Sprite help_background;
						help_background.setTexture(help_png);
						help_background.setScale(3.5f, 3.5f);
						help_background.setPosition(help.getSize().x / 8, help.getSize().y / 25);
						
						while (help.isOpen())
						{
							Event aevent;
							while (help.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									help.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										help.close();
									}
								}
							}


							//about.close();
							help.clear();
							help.draw(help_background);
							help.display();
						}
						MENU.create(VideoMode(960, 720), "Main Menu", Style::Default);
						MENU.setFramerateLimit(60);
					}
					if (x == 2)
					{
						MENU.close();
						RenderWindow about(VideoMode(960, 720), "ABOUT");
						while (about.isOpen())
						{

							Event aevent;
							while (about.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									about.close();
									

								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										about.close();
									}
								}

							}


							//help.close();
							about.clear();
							about.display();

						}
						MENU.create(VideoMode(960, 720), "Main Menu", Style::Default);
						MENU.setFramerateLimit(60);
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
