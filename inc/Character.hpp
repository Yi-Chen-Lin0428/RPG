/*****************************************************************//**
 * \file   Character.hpp
 * \brief  ¨¤¦âÃþ§O
 * 
 * registered func:
 *     -moveMentEventHandler(moveMentEvent& eve)
 *	   -attackEventHandler(attackEvent& eve)
 * 
 * \author LIN, YiChen
 * \date   2024.11.12 *********************************************************************/
#pragma once

#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_

#include <string>
#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "Text.hpp"
#include "EventSystem.hpp"
#include "CollisonDetecter.hpp"
#include "AnimationComponent.hpp"
#include "AllItems.hpp"
#include "LifeEntity.hpp"

class Character : LifeEntity
{
public:
	Character(EventSystem& _eventSys, int _role, std::string _name, int _initMap);
	~Character();

	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);
	void move(sf::Vector2f d);
	void triggerHandler(std::vector<triggerObj_typedef>& triggerObj);
	void update(std::vector<sf::FloatRect>& fr);
	void draw(sf::RenderWindow& win);
	sf::FloatRect getGBnds();

private:
    LiftEntityInitTypeDef* initLifeEntity();
	void initAnimation();
	void initSprite();
	void initTexture();
	void initPos(sf::Vector2f pos);
	void updateAnimation(Direction _movement);

	void attackEventHandler(attackEvent& eve);
	void moveMentEventHandler(moveMentEvent& eve);
	void collisonHandler(std::vector<sf::FloatRect>& fr);
	void equipEventHandler(equipEvent& eve);

	AnimationComponent* animationComponent;
	EventSystem& eventSys;
	Text name;
	Weapon *weapon;
	DIR dir;
	sf::Texture  characterTexture;
	sf::Sprite   player, weaponSprite;
	sf::Vector2f dis, lastPos;
	sf::FloatRect nextBnds;
	sf::RectangleShape playerBBox;

	int role;
	int curMap;
	bool moved, UIListening, changeWeapon = 0;

	sf::Vector2f mapInitPos[5] =
	{
		sf::Vector2f(285.f, 145.f),
		sf::Vector2f(928.f, 200.f),
		sf::Vector2f(520.f, 608.f),
		sf::Vector2f(10.f , 345.f),
		sf::Vector2f(95.f , 5.f)
	};
};
#endif // _CHARACTER_HPP_
