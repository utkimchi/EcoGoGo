#pragma optimize("",off)
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <windows.h>
#include "ses_classes.h"

//sf::VideoMode::getDesktopMode().width
//sf::VideoMode::getDesktopMode().height
int width = 1600;
int height = 1200;



int main()
{
	//WINDOW
	sf::RenderWindow window;
	window.create(sf::VideoMode(width, height), "EcoGoGo!", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	//TEXTURES
	sf::Texture ph;
	if (!ph.loadFromFile("ph.jpg"))
	{
		std::cout << "PH TEXTURE NOT LOADED";
	}

	//FONT
	sf::Font chrono;
	chrono.loadFromFile("media/chrono.ttf");

	//CHARACTER WINDOW
	bool showRect = true;
	sf::RectangleShape spbord;
	spbord.setSize(sf::Vector2f(500, 750));
	spbord.setPosition(40, 25);
	spbord.setOutlineColor(sf::Color::White);
	spbord.setOutlineThickness(5);
	spbord.setFillColor(sf::Color::Black);
	//Sprite when clicked on
	sf::Sprite spwi;

	//CHARACTER TEXT
	bool showText = true;
	sf::RectangleShape sptbord;
	sptbord.setSize(sf::Vector2f(500, 250));
	sptbord.setPosition(40, 810);
	sptbord.setOutlineColor(sf::Color::White);
	sptbord.setOutlineThickness(5);
	sptbord.setFillColor(sf::Color::Black);

	sf::Text cName("", chrono);
	cName.setCharacterSize(50);
	//sf::Text cKnow("Knowledge ~ ", chrono);
	//sf::Text cLeader("Leadership ~", chrono);
	cName.setPosition(50, 815);



	//Images
	sf::Texture col, sus, ham, mar, llo;
	if (!col.loadFromFile("media/colton_pix.png")) { return -1; }
	if (!sus.loadFromFile("media/sus_pix.png")) { return -1; }
	if (!ham.loadFromFile("media/hamb_pix.png")) { return -1; }
	if (!mar.loadFromFile("media/mark_pix.png")) { return -1; }
	if (!llo.loadFromFile("media/lloyd_pix.png")) { return -1; }
	//User Groups
	Users home;
	//Size (a b) pos c d
	home.setArea(sf::Vector2f(995, 800), 565, 25, sf::Color::White);
	//Postion x y Size z q -- Should be (c, d+5,a-5,b-5)
	sf::IntRect hR(565, 30, 990, 795);

	//Name, Leadership, Knowledge, Belief, Texture, Size, Bounding Box, Max Speed
	Agent firstGuy("Colton", 5, 8, "Thin Man", ph,50, hR, 5,col);
	Agent secondGuy("Susan", 5, 8, "Beautiful Lady", ph, 45,hR, 5,sus);
	Agent cat("Hambone", 5, 8, "Chaotic Being", ph,  40, hR, 5,ham);
	Agent thirdGuy("Mark", 5, 8, "True King", ph, 40,hR, 5,mar);
	Agent fourthGuy("Lloyd", 5, 8, "Tree Whisperer", ph,40, hR, 5,llo);
	home.addUser(firstGuy);
	home.addUser(secondGuy);
	home.addUser(cat);
	home.addUser(thirdGuy);
	home.addUser(fourthGuy);
	home.printUsers();


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					bool black = true;
					for (auto &b : home.agents) {

						if (b.body.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						{
							std::cout << "Clicked a(n) " << b.mBelief << " named " << b.getName() << "\n";
							spwi = b.face;
							cName.setString(b.getName() + " ~ " + b.mBelief);
							black = false;
							showRect = false;
							showText = false;
						}
					}
					if (black) {
						showRect = true;
						showText = true;
						cName.setString("");
						//sf::Text cKnow("Knowledge ~ ", chrono);
						//sf::Text cLeader("Leadership ~", chrono);
						black = true;
					}
				}

			default:
				break;
			}
		}
		//Draw here window.draw(...)

		window.clear(sf::Color::Black);
		window.draw(spbord);
		window.draw(sptbord);

		if (!showRect) {
			window.draw(spwi);
			window.draw(cName);
		}
		window.draw(home.area);

		for (auto& c : home.connections())
		{
			window.draw(c);
		}

		for (auto& a : home.agents)
		{
			a.wander();
			window.draw(a.body);
		}

		window.display();
	}

	return 0;
}