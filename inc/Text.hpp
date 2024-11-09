#pragma once

#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

class Text
{
public:
	sf::Text text;

	Text();
	~Text();
	void initText(int _size, std::string _s_string, sf::Color _color = sf::Color::White, bool setOrgAtCenter = 1, std::string _font = "Arial", sf::Uint32 _style = sf::Text::Regular);
	void initText(int _size, int _s_string, sf::Color _color = sf::Color::White, bool setOrgAtCenter = 1, std::string _font = "Arial", sf::Uint32 _style = sf::Text::Regular);
	void setPos(float x, float y);

private:
	std::string font_t;
	std::string s_string;
	sf::Color color;
	sf::Font font;
	sf::Uint32 style;
	sf::FloatRect textRect;
	int size;
};
#endif // _TEXT_HPP_