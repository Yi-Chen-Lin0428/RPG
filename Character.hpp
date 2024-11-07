#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Character
{
public:
	Character(int _role);
	~Character();

	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);
	void move(sf::Vector2f d);
	void setSpd(int s);
	int getSpd();
	void update(std::vector<sf::FloatRect>& fr);
	void draw(sf::RenderWindow& win);
	sf::FloatRect getGBnds();
private:
	
	bool isIntersect(sf::FloatRect fr, std::vector<sf::FloatRect>& frList);
	void initSprite();
	void initTexture();
	void initPos(sf::Vector2f pos);

	sf::Texture  characterTexture;
	sf::Sprite   player;
	sf::Vector2f dis, lastPos;
	//sf::Vector2f characterPos;
	sf::FloatRect nextBnds;

	bool isCollided;
	int role;
	int spd;

};
#endif // _CHARACTER_HPP_
