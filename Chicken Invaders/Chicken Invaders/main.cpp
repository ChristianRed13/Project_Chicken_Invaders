#include <iostream>
#include<fstream>
#include<ios>
#include<map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "GameFrame.h"
#include "MainMenu.h"
#include "NewGame.h"

using namespace sf;

bool cmp(pair<std::string, int>& a,
	pair<std::string, int>& b)
{
	return a.second > b.second;
}

std::string sort(std::map<std::string, int> &M)
{
	int repeat = 0;
	std::string text;

	// Declare vector of pairs
	vector<pair<std::string, int> > A;

	// Copy key-value pair from Map
	// to vector of pairs
	for (auto& it : M) {
		A.push_back(it);
	}
	// Sort using comparator function
	sort(A.begin(), A.end(), cmp);

	for (size_t i = 0; i < A.size() && repeat <= 10; i++)
	{
		text += A[i].first + std::to_string(A[i].second) + "\n";
	}
	
	return text;
}

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
						MENU.close();MENU.close();
						NewGame newGame(960, 720);
						while (newGame.getWindowIsOpen())
						{
							newGame.update();

							newGame.render();
						}
						if (newGame.isUserFieldCompleted() == false && newGame.getEvent().key.code != sf::Keyboard::Escape) {
							GameFrame gameFrame(newGame.getUser());
							while (gameFrame.getWindowIsOpen())
							{
								gameFrame.update();

								//if hp == 0 -> window.close()
								gameFrame.render();
							}
							std::ofstream scores("Hall-Of-Fame.txt", std::ios_base::app | std::ios_base::out);
							scores << gameFrame.getPlayerName() << ": " << gameFrame.getScore() << endl;
							scores.close();
						}
						MENU.create(VideoMode(960, 720), "Main Menu", Style::Default);
						MENU.setFramerateLimit(60);
					}
					if (x == 1)
					{
						MENU.close();
						RenderWindow help(VideoMode(960, 720), "HELP");
						help.setFramerateLimit(60);
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

						sf::Font font;
						font.loadFromFile("Fonts/PressStart2P-Regular.ttf");
						std::string finalText;

						
						std::map< std::string, int > name_score;
						std::string text;
						int value;

						ifstream scores;
						scores.open("Hall-Of-Fame.txt");
						std::string line;
						while (scores >> text >> value)
							name_score[text] = value;
						

						finalText = sort(name_score);

						sf::Text showTxt(finalText, font);
						showTxt.setFillColor(sf::Color::White);
						showTxt.setPosition(370, 150);
						RenderWindow hell_of_fame(VideoMode(960, 720), "Scores");
						hell_of_fame.setFramerateLimit(60);

						while (hell_of_fame.isOpen())
						{


							Event aevent;
							while (hell_of_fame.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
									hell_of_fame.close();

								if (aevent.type == Event::KeyPressed)
									if (aevent.key.code == Keyboard::Escape)
										hell_of_fame.close();

							}


							//help.close();
							hell_of_fame.clear();

							hell_of_fame.draw(showTxt);

							hell_of_fame.display();

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
