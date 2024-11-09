#pragma once

#ifndef _BAG_HPP_
#define _BAG_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AllItems.hpp"
#include "EventSystem.hpp"
#include "Button.hpp"
#include <array>
#include "Text.hpp"

enum class BagButtonType 
{
    CloseBag,
    Equip,
    Next,
    Last,
    Item1,
    Item2,
    Item3,
    Item4,
    Item5,
    Item6,
    Item7,
    Item8,
    Item9,
    Unknown
};

static const std::map<std::string, BagButtonType> BagButtonMap = 
{
    {"closeBag", BagButtonType::CloseBag},
    {"equip",    BagButtonType::Equip},
    {"next",     BagButtonType::Next},
    {"last",     BagButtonType::Last},
    {"item1",    BagButtonType::Item1},
    {"item2",    BagButtonType::Item2},
    {"item3",    BagButtonType::Item3},
    {"item4",    BagButtonType::Item4},
    {"item5",    BagButtonType::Item5},
    {"item6",    BagButtonType::Item6},
    {"item7",    BagButtonType::Item7},
    {"item8",    BagButtonType::Item8},
    {"item9",    BagButtonType::Item9}
};

extern std::array<sf::Vector2f, 9> dispPos;

class Bag
{
public:
	Bag(EventSystem& _eventSys);
	~Bag();

	void update();
	void draw(sf::RenderWindow& win);
	void addWeapon(Weapon*);
	void sellWeapon(Weapon* weapon);

private:
    void initButtons();
    void initBagUI();
    void deleteBtns();
    void deleteWeapons();

    void openBagEventHandler(openBagEvent& eve);
    void mouseEventHandler(mouseEvent& eve);
    void boughtEventHandler(boughtEvent& eve);
    void closeUIEventHandler(closeUIEvent& eve);

	EventSystem& eventSys;
    MouseState mouseState;
	sf::Sprite UI;
	sf::Texture UITexture;
	std::vector<Weapon*> weaponList;
	std::vector<Button*> btnList;
    std::vector<Text*> textList;

	bool isOpened = 0, boughtEve = 0;
    int selector;
};
#endif // _BAG_HPP_
