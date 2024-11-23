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

//�sĲ�o�����O�A�W�١A�x�ήy��
typedef struct
{
	std::string oClass;
	std::string oName;
	sf::FloatRect oRect;
}triggerObj_typedef;


/**
 * \brief  �˴����a�P��ê�����I��
 * \param  ���a��m
 * \param  ��ê���C��
 * \return <0>:�I�������A�b���h�����l�׬�0
 * \return <1>:�O�_�I��
 */
bool collisonDetect(sf::FloatRect playerRect, std::vector<sf::FloatRect>& obstacleList);

/**
 * \brief  �˴����a�P�U��Ĳ�o���I��
 * \param  ���a��m
 * \param  Ĳ�o���������c�C��
 * \return <0>:�I�������c��
 * \return <1>:�O�_�I��
 */
std::pair<triggerObj_typedef, bool> collisonDetect(sf::FloatRect playerRect, std::vector<triggerObj_typedef>& obstacleList);

#endif // _COLLISON_DETECTER_HPP_

