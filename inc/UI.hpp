#pragma once

#ifndef _UI_HPP_
#define _UI_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "EventSystem.hpp"
#include "Button.hpp"
#include "Text.hpp"

#define BAR_FILLER_X_BASE_COORDINATE 58
#define BAR_FILLER_Y_BASE_COORDINATE 16
#define BAR_Y_OFFSET                 32
#define BAR_WIDTH                    188
#define BAR_HEIGHT                   32

class UI
{
public:
	UI(EventSystem& _eventSys);
	~UI();

	void dispUI(sf::RenderWindow& win);

private:
	void dispHP();
	void dispMP();
	void dispLevel();
	void dispBtns();
	void dispMonsters();

	int mapHP2Bar(int);
	int mapMP2Bar(int);
	int mapLevel2Bar(int);

	void initButtons();
	void deleteBtns();
	void initUISprite();
	void initBars();

	EventSystem& eventSys;
	std::vector<Button*> btnList;
	sf::Sprite UISprite;
	sf::Texture UITexture;
	sf::RectangleShape HPBar, MPBar, levelBar;
};
#endif // _UI_HPP_
