/*****************************************************************//**
 * \file   InputController.hpp
 * \brief  �ھڷ�e�ƥ�Q�Ϊ��A�����t��L��J
 *		   �������ҲաA�H�εo���ƹ��ƥ�
 * 
 * ���仡��: 
 *   (B) -> ���}/�����I�]
 *   (H) -> ���}/�����ө�
 *			   
 *		
 * 
 * registered func:
 *     -openProFileEventHandler(openProFileEvent& eve)
 *     -openShopEventHandler(openShopEvent& eve)
 *     -closeUIEventHandler(closeUIEvent& eve)
 * 
 * \author LIN, YiChen
 * \date   2024.11.12
 *********************************************************************/

#pragma once

#ifndef _INPUT_CONTROLLER_HPP_
#define _INPUT_CONTROLLER_HPP_

#include <SFML/Graphics.hpp>
#include "EventSystem.hpp"

class InputController
{
public:
	InputController(EventSystem& _eventSys);
	~InputController();

	/**
	 * \brief �b�D�C���j��C�V���y����
	 * note:
	 * �ھڷ�e�������A�۰ʱN��J�]�ƪ��A�o���������ҲաA
	 * ��p��e�B��ө������A�h����}�Ⲿ�ʡA�N��V�䪬�A
	 * ��o���ө��Ω�UI�椬�A�Ϥ��h��o������i�沾���޿�
	 */
	void inputScan(sf::RenderWindow& win);

private:
	void handleKeyB(bool closeBtnSync);
	void handleKeyH(bool closeBtnSync);
	void publish(Event& eve);

	void openProFileEventHandler(openProFileEvent& eve);
	void openShopEventHandler(openShopEvent& eve);
	void closeUIEventHandler(closeUIEvent& eve);

	EventSystem& eventSys;
	sf::Clock scanSpd;
	DIR dir;

	int currentS = 0, nextS = 0;

	enum outputState
	{
		character,
		proFileUI,
		shopUI,
		bagUI
	};
};
#endif // _INPUT_CONTROLLER_HPP_
