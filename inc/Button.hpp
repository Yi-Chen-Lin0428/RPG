#pragma once

#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AnimationComponent.hpp"
#include "EventSystem.hpp"

enum btnState { idle, mouseOver, clicked };

class Button
{
public:
	Button(std::string _name, sf::Vector2f pos, std::string texturePath, int w, int h, float xScale = 1, float yScale = 1);
	~Button();

	int getState(MouseState& _mouseState);
	sf::Sprite getSprite();
	std::string getName();

private:
	void initAnimation();
	bool isClicked();
	bool isMouseOver();

	MouseState mouseState;
	AnimationComponent *animationComponent;
	sf::Sprite btn;
	sf::Texture btnTexture;
	std::string name;

	int currentState;
	bool lastState, _currentState;
};
#endif // _BUTTON_HPP_
