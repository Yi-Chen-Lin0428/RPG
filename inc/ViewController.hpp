/*****************************************************************//**
 * \file   ViewController.hpp
 * \brief  ����C�������A���ƥ�t�γq�H�A
 *		   �U�Ҳեi�ШD���������A�H�b���T��m��V����
 * 
 * \author YichenLin
 * \date   2024.11.23
 *********************************************************************/

#pragma once

#ifndef _VIEW_CONTROLLER_HPP_
#define _VIEW_CONTROLLER_HPP_

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "EventSystem.hpp"

class ViewController
{
public:
	ViewController(EventSystem& _eventSys, sf::RenderWindow* _win, int V_width, int V_height, int M_width, int M_height);
	~ViewController();

	void updateView(sf::Vector2f centerPos);

private:
	sf::Vector2f limitViewPos(sf::Vector2f pos);

	void reqDfViewEventHandler(ReqDfViewEvent& eve);
	void reqCurViewEventHandler(ReqCurViewEvent& eve);

	EventSystem& eventSys;
	sf::View view;
	sf::RenderWindow* win;

	int vW, vH, mW, mH;
};
#endif // _VIEW_CONTROLLER_HPP_
