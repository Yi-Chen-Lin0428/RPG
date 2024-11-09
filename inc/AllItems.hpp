/*****************************************************************//**
 * \file   AllItems.hpp
 * \brief  所有物品定義，目前只做到武器裝備
 * 
 * TODO    設計所有物品的基類，統一接口
 * 
 * \author macma
 * \date   November 2024
 *********************************************************************/

#pragma once

#ifndef _ALLITEMS_HPP_
#define _ALLITEMS_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AnimationComponent.hpp"
//#include "EventSystem.hpp"

enum class Direction {
	Up,
	Down,
	Left,
	Right,
	Idle
};

////////////////////////////////////////////////////////////////////////////
///                                                                      ///
///                               子彈類別                                ///
///                                                                      ///
////////////////////////////////////////////////////////////////////////////
class Bullet {

public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir, float speed);

	void update(float dt);
	void draw(sf::RenderWindow& window);
	bool isAlive() const;

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
	sf::CircleShape shape;
	bool alive;
};

////////////////////////////////////////////////////////////////////////////
///                                                                      ///
///                               基礎類別                                ///
///                                                                      ///
////////////////////////////////////////////////////////////////////////////
class Weapon
{
public:
	Weapon(std::string _name, int _size, int _price, int _damage, int _atkSpeed, std::string texturePath);
	virtual ~Weapon() = default;

	void init();
	//getter and setter
    void setPos(float x, float y);
	const sf::Vector2f getPos();
	const sf::Sprite getSprite();
	const std::string getName() const;
	const int getWeight() const;
	const int getDamage() const;
	const int getPrice() const;

	virtual void update(const sf::Vector2f& _playerPos, Direction _movement, sf::Vector2f& _dis);
	virtual void draw(sf::RenderWindow& win);
	virtual Weapon* clone() const = 0;
	virtual void attack(sf::Vector2f target_pos, sf::Vector2f playerPos);

protected:
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape BBox;
	sf::Vector2f dis;

	int size;
	int price;
	int damage;
	int atkSpeed;
	bool isUsed = 0;
};

class Armor
{
public:
	Armor(std::string _name, int _size, int _price, int _defenseVal, std::string texturePath);
	virtual ~Armor() = default;

	sf::Sprite getSprite();
	std::string getName() const;

	virtual Armor* clone() const = 0;
	virtual int getWeight() const;
	virtual void defense() = 0;

private:
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;

	int size;
	int price;
	int defenseVal;
};

class Potion
{
public:
	Potion(std::string _name, int _size, int _price, int _val, std::string texturePath);
	virtual ~Potion() = default;

	sf::Sprite getSprite();
	std::string getName() const;

	virtual Potion* clone() const = 0;
	virtual int getWeight() const;
	virtual void use() = 0;

private:
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;

	int size;
	int price;
	int val;
};


////////////////////////////////////////////////////////////////////////////
///                                                                      ///
///                               衍生類別                                ///
///                                                                      ///
////////////////////////////////////////////////////////////////////////////
class Ax : public Weapon
{
public:
	Ax();
	~Ax() = default;

	void attack(sf::Vector2f target_pos, sf::Vector2f playerPos) override;
	Weapon* clone() const override;

private:

};

class Pistol : public Weapon
{
public:
	Pistol();
	~Pistol() = default;

	void attack(sf::Vector2f target_pos, sf::Vector2f playerPos) override;
	Weapon* clone() const override;

private:

};

class Rifle : public Weapon
{
public:
	Rifle();
	~Rifle() = default;

	void update(const sf::Vector2f& _playerPos, Direction _movement, sf::Vector2f& _dis) override;
	void draw(sf::RenderWindow& win) override;
	void attack(sf::Vector2f target_pos, sf::Vector2f playerPos) override;
	Weapon* clone() const override;

private:
	std::vector<Bullet> bulletList;
	sf::Clock fireSpd;
	Direction dir;
};

class Knife : public Weapon
{
public:
	Knife();
	~Knife() = default;

	void attack(sf::Vector2f target_pos, sf::Vector2f playerPos) override;
	Weapon* clone() const override;

private:

};

class Pump : public Weapon
{
public:
	Pump();
	~Pump() = default;

	void attack(sf::Vector2f target_pos, sf::Vector2f playerPos) override;
	Weapon* clone() const override;

private:

};

class None : public Weapon
{
public:
	None();
	~None() = default;

	void attack(sf::Vector2f target_pos, sf::Vector2f playerPos) override;
	Weapon* clone() const override;

private:

};

#endif // _ALLITEMS_HPP_
