#pragma once

#ifndef _COLLISON_DETECTER_HPP_
#define _COLLISON_DETECTER_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <tuple>
#include <unordered_map>

enum
{
	sw2map0,
	sw2map1,
	sw2map2,
	sw2map3,
	sw2map4,
	blood_bag,
	shop1,
	shop2,
	shop3,
	bed
};


extern std::unordered_map<std::string, int> getTriggerType;

//存觸發器類別，名稱，矩形座標
typedef struct
{
	std::string oClass;
	std::string oName;
	sf::FloatRect oRect;
}triggerObj_typedef;


/**
 * \brief  檢測玩家與障礙物的碰撞
 * \param  玩家位置
 * \param  障礙物列表
 * \return <0>:碰撞類型，在此多載中始終為0
 * \return <1>:是否碰撞
 */
bool collisonDetect(sf::FloatRect playerRect, std::vector<sf::FloatRect>& obstacleList);

/**
 * \brief  檢測玩家與各種觸發器碰撞
 * \param  玩家位置
 * \param  觸發器類型結構列表
 * \return <0>:碰撞物結構體
 * \return <1>:是否碰撞
 */
std::pair<triggerObj_typedef, bool> collisonDetect(sf::FloatRect playerRect, std::vector<triggerObj_typedef>& obstacleList);

#endif // _COLLISON_DETECTER_HPP_

