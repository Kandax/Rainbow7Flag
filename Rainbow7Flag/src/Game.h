#pragma once
#include <string>


#include "SFML/Graphics.hpp"



class Game
{
public:
	Game();
	void run();
private:
	void events();
	void input();
	void updatePhysics();
	void update();
	void render();

private:

	uint16_t mWindowWidth;
	uint16_t mWindowHeight;
	std::string mWindowName;

	sf::RenderWindow mWindow;
	sf::Event mEvent;



};

