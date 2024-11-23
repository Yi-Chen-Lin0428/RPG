/*********************************************************************
 * \file   MapManager.hpp
 * \brief  �a�Ϻ޲z���A�t�d�a�ϥ[���A�ϼh��V�A�a�Ϥ����A�åi��^�a�ϩҦ��귽
 *	       ��V�w: "SFMLOrthogonalLayer.hpp"�OtmxLite���Ѫ�����2D�a�ϴ�V��
 *		   �ӷ�:https://github.com/fallahn/tmxlite/blob/master/SFMLExample/src/SFMLOrthogonalLayer.hpp
 * 
 * registered func:
 *     -mapSwitchEventHandler(mapSwitchEvent& eve)
 * 
 * \author Lin, YiChen
 * \date   2024.11.7
 *********************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"
#include "Text.hpp"
#include "EventSystem.hpp"
#include "CollisonDetecter.hpp"


#define MAP_WIDTH  (int)960 ///�a�ϼe��
#define MAP_HIGHTH (int)640 ///�a�ϰ���
#define MAP_QTY    5        ///�a�ϼƶq

/**
 * \brief  �޲z�Ҧ��a�ϸ��J�A�����A��V�A��s�A�I���˴����ާ@
 */
class MapManager
{
public:
	MapManager(EventSystem& eventSys, int initMap);
	~MapManager();
	void update();
	void draw(sf::RenderWindow& win);
	void setLayerQty();
	int getLayerQty();
	int getCurMap();
	void setCurMap(const int mapNum);
	const tmx::Map& getCMap();
	void setCMap(tmx::Map&& _cmap);
	std::vector<sf::FloatRect>& getCollObjs();
	std::vector<triggerObj_typedef>& getTriggerObjs();

private:
	bool LoadMap(tmx::Map* _map, std::string mapPath); //unused
	template <class T>
	void loadObjs(std::vector<T>& RectList, std::string layerName);
	void showMapNameFor3Sec();
	void delLayerPtr();

	void mapSwitchEventHandler(mapSwitchEvent& eve);

	EventSystem& eventSys;
	Text mapName_Show;
	std::vector<tmx::Map> mapList;
	std::vector<MapLayer*> layerList;
	std::vector<sf::FloatRect> collObjList;
	std::vector<triggerObj_typedef> triggerObjList;
	tmx::Map curCMap;
	sf::Clock clk;
	sf::Font font;

	int curMapID;   
	int lastMapID;
	int layerQty;

	enum mapNum
	{
		hall,
		matrix,
		yard,
		garage,
		gas_tation
	};

	std::string mapNames[MAP_QTY] = {
		"Hall", 
		"Matrix", 
		"Yard", 
		"Garage", 
		"Gas_Station"
	};
};



