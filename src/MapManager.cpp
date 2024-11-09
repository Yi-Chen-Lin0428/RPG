/**
 * notes:
 *   1，tmx::Map禁止使用'='傳遞地圖，這裡用std::move解決，
 *      地圖用完要記得還回去。
 *	 2，更新函式應放在遊戲回圈內才能刷新數據
 * 
 *   TODO 把觸發器信息用結構包裝以利判斷
 */

#include "MapManager.hpp"

MapManager::MapManager(EventSystem& _eventSys, int initMap)
    : eventSys(_eventSys), curMapID(initMap)
{
	/*------------------註冊call back函式------------------*/
	eventSys.subscribe<mapSwitchEvent>(EventType::e_mapSwitch, [this](mapSwitchEvent& eve)
	{
		this->mapSwitchEventHandler(eve);
	});
	/*----------------------------------------------------*/
	//根據地圖個數建立地圖實體
	for (int i = 0; i < MAP_QTY; i++)
	{
		tmx::Map tmpMap;

		if (!tmpMap.load("./resources/" + mapNames[i] + ".tmx"))
		{
			//std::cerr << "can't find map form " << mapPaths[i] << std::endl;
			break;
		}
		std::cout << "INFO: found map from" << "./resources/" + mapNames[i] + ".tmx" << std::endl;

		mapList.emplace_back(std::move(tmpMap)); 
	}
	if (mapList.size() != MAP_QTY) //確認是否正確讀完地圖
	{
		std::cerr << "ERROR: MapManager init failed" << std::endl;
	}
	else
	{
		std::cout << "INFO: MapManager init successed" << std::endl;
	}
	//初始化內部變量
	this->setCMap(std::move(mapList[curMapID]));
	this->loadObjs(collObjList, "collison");
	this->loadObjs(triggerObjList, "trigger");
	this->setLayerQty();

	//建立初始圖層
	for (int i = 0; i < layerQty; i++)
	{
		layerList.emplace_back(new MapLayer(curCMap, i));
	}

	mapName_Show.initText(60, mapNames[curMapID]);
	clk.restart();
}

MapManager::~MapManager()
{
	this->delLayerPtr();
	mapList.clear();
}

void MapManager::update() //放在遊戲回圈內
{
	if (curMapID != lastMapID)
	{
		mapList[lastMapID] = std::move(curCMap);     //把舊地圖所有權丟回給地圖清單
		lastMapID = curMapID;
		this->setCurMap(curMapID);                   //更新地圖索引
		std::cout << "INFO: switched map to number " << curMapID << std::endl;
		this->setCMap(std::move(mapList[curMapID])); //更新地圖實體
		this->setLayerQty();                         //更新圖層數量
		this->loadObjs(collObjList, "collison");    
		this->loadObjs(triggerObjList, "trigger");
		
#ifdef DEBUG
		std::cout << "INFO: layerQty = " << layerQty << std::endl;
#endif // DEBUG

		this->delLayerPtr();

		for (int i = 0; i < layerQty; i++)            //根據新地圖更新所有圖層
		{
			layerList.emplace_back(new MapLayer(getCMap(), i));
		}

		mapName_Show.text.setString(mapNames[curMapID]);
		clk.restart();
	}
	this->showMapNameFor3Sec();
}

void MapManager::draw(sf::RenderWindow& win)
{
	static ReqDfViewEvent reqDfVEve;
	static ReqCurViewEvent reqCurVEve;

	for (auto& layer : layerList)
	{
		win.draw(*layer); 
	}

	SetDefaultView(reqDfVEve);
	mapName_Show.text.setPosition(win.getSize().x / 2.f - 
		                          mapName_Show.text.getGlobalBounds().width / 2.f, 50.f);
	win.draw(mapName_Show.text);
	SetCurrentView(reqCurVEve);
}

void MapManager::setLayerQty()
{
	layerQty = (int)curCMap.getLayers().size();
}

int MapManager::getLayerQty()
{
	return (int)curCMap.getLayers().size();
}

int MapManager::getCurMap()
{
	return curMapID;
}

void MapManager::setCurMap(const int mapNum)
{
	curMapID = mapNum;
}

const tmx::Map& MapManager::getCMap()
{
	return curCMap;
}

void MapManager::setCMap(tmx::Map&& _cmap)
{
	curCMap = std::move(_cmap);
}

std::vector<sf::FloatRect>& MapManager::getCollObjs()
{
	return collObjList;
}

std::vector<triggerObj_typedef>& MapManager::getTriggerObjs()
{
	return triggerObjList;
}

void MapManager::mapSwitchEventHandler(mapSwitchEvent& eve)
{
	lastMapID = curMapID;
	setCurMap(eve.newMapID);
}

void MapManager::showMapNameFor3Sec()
{
	if (clk.getElapsedTime().asSeconds() > 3)
	{
		mapName_Show.text.setString(""); 
	}
}

void MapManager::delLayerPtr()
{
	for (auto* layer : layerList) {
		delete layer;
	}
	layerList.clear();
}

template <class T>
void MapManager::loadObjs(std::vector<T>& RectList, std::string layerName)
{
	RectList.clear(); //清空碰撞框
	for (const auto& layer : curCMap.getLayers()) //遍歷圖層
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			//
			const auto& objLayer = layer->getLayerAs<tmx::ObjectGroup>();
			if (objLayer.getName() == layerName)
			{
				for (const auto& obj : objLayer.getObjects())
				{
					float x = obj.getPosition().x;
					float y = obj.getPosition().y;
					float width = obj.getAABB().width;
					float height = obj.getAABB().height;

					sf::FloatRect tmpFRect(x, y, width, height);

					if constexpr (std::is_same<T, sf::FloatRect>::value) 
					{	
						RectList.emplace_back(tmpFRect);
					}
					else if constexpr (std::is_same<T, triggerObj_typedef>::value)
					{
						triggerObj_typedef triggerObj;
						triggerObj.oClass = obj.getClass();
						triggerObj.oName = obj.getName();
						triggerObj.oRect = tmpFRect;
						RectList.emplace_back(triggerObj);
						//std::cout << "\ntriggerObj.oClass = " << obj.getClass()
						//	      << "\ntriggerObj.oName  = " << obj.getName()
						//	      << std::endl;
					}
				}
				break;
			}
		}
	}

#ifdef DEBUG
	std::cout << "INFO: "
		      << std::setw(8) << std::left << layerName
		      << "Object Qty = " << RectList.size() << std::endl;
#endif // DEBUG
}

bool MapManager::LoadMap(tmx::Map* _map, std::string mapPath)
{
	return _map->load(mapPath);
}
