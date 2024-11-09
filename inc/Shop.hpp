/*****************************************************************//**
 * \file   Shop.hpp
 * \brief  商店管理器，目前只做到武器購買
 * 
 * registered func:
 *     -moveMentEventHandler(moveMentEvent& eve)
 *     -openShopEventHandler(openShopEvent& eve)
 *     -mouseEventHandler(mouseEvent& eve)
 * 
 * \author LIN, YiChen
 * \date   2024.11.12
 *********************************************************************/

#pragma once

#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <fstream>
#include "EventSystem.hpp"
#include "SFMLOrthogonalLayer.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "AllItems.hpp"

#define TEXT_SIZE 22

enum class ButtonType {
    Close,
    Purchase,
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
    Unknown
};

static const std::map<std::string, ButtonType> buttonMap = {
    {"close",    ButtonType::Close},
    {"purchase", ButtonType::Purchase},
    {"next",     ButtonType::Next},
    {"last",     ButtonType::Last},
    {"item1",    ButtonType::Item1},
    {"item2",    ButtonType::Item2},
    {"item3",    ButtonType::Item3},
    {"item4",    ButtonType::Item4},
    {"item5",    ButtonType::Item5},
    {"item6",    ButtonType::Item6},
    {"item7",    ButtonType::Item7},
    {"item8",    ButtonType::Item8},
};

class Shop
{
public:
	Shop(EventSystem& _eventSys);
	~Shop();

	void update();
	void draw(sf::RenderWindow& win);

private:
    void initTextPos();
	void initTexture(std::string _UITexture);
	void initButtons();
    void initShopData();
    void dispShoppingCart();
    void purchaseHandler();
	void switchShop(bool _dir);
	void deleteBtns();
    void deleteWeapons();

	void mouseEventHandler(mouseEvent& eve);
	void moveMentEventHandler(moveMentEvent& eve);
	void openShopEventHandler(openShopEvent& eve);
    void closeUIEventHandler(closeUIEvent& eve);

	EventSystem& eventSys;
	Text shopName, itemName, itemWeight, itemPrice, itemDamage, itemDefense;
	DIR dir;
	MouseState mouseState;
	std::string getShopName[3];
	std::vector<Button*> btnList;
    std::vector<Weapon*> weaponList;
	sf::Sprite UI;
    sf::Sprite tmpSprite;
	sf::Texture UITexture;

	bool isOpened;
	int shopID;
	int shoppingCart;
};
#endif // _SHOP_HPP_





