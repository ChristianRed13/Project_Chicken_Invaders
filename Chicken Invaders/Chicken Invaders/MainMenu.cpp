#include "MainMenu.h"
#include <iostream>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("Fonts/PressStart2P-Regular.ttf")) {
        std::cout << "No font is here";
    }
    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(350, 150);
    //Help
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Help");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(350, 270);
    //About
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Scores");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(350, 390);
    //Exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(350, 510);

    MainMenuSelected = -1;

}

void MainMenu::draw(RenderWindow& window)
{
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }
}

void MainMenu :: MoveUp()
{
    if (MainMenuSelected - 1 >= -1) {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected--;
        if (MainMenuSelected == -1) 
        {
            MainMenuSelected = 3;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

void MainMenu::MoveDown()
{
    if (MainMenuSelected + 1 <= Max_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;
            if (MainMenuSelected == 4)
            {
                MainMenuSelected = 0;
            }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

MainMenu::~MainMenu()
{
}
