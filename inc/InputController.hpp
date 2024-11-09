/*****************************************************************//**
 * \file   InputController.hpp
 * \brief  根據當前事件利用狀態機分配鍵盤輸入
 *		   給相應模組，以及發布滑鼠事件
 * 
 * 按鍵說明: 
 *   (B) -> 打開/關閉背包
 *   (H) -> 打開/關閉商店
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
	 * \brief 在主遊戲迴圈每幀掃描按鍵
	 * note:
	 * 根據當前視窗狀態自動將輸入設備狀態發布給相應模組，
	 * 比如當前處於商店視窗，則停止腳色移動，將方向鍵狀態
	 * 轉發給商店用於UI交互，反之則轉發給角色進行移動邏輯
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
