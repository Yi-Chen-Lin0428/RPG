/*****************************************************************//**
 * \file   EventConfig.hpp
 * \brief  所有事件體的定義都放在這個文件統一管理，
 *         並由事件管理器引用
 * 
 * \author YichenLin
 * \date   2024.11.10
 *********************************************************************/

#pragma once

#include "AllItems.hpp"

enum class EventType //事件uid
{
    e_mapSwitch,   //地圖切換
    e_openShop,    //進入商店
    e_openProFile, //打開角色資訊欄
    e_closeUI,     //關閉任何UI
    e_moveMent,    //移動事件(WSAD)
    e_mouse,       //滑鼠狀態
    e_bought,      //購買(從商店購買或角色放回背包)
    e_openBag,     //打開背包
    e_equip,       //裝備物品(從背包到角色)
    e_attack,
    e_reqDfV,
    e_reqCurV
};

class Event //事件基類
{
public:
    virtual ~Event() = default;
    virtual EventType getType() const = 0;
};

#define SetDefaultView(x) eventSys.publish(x)
class ReqDfViewEvent : public Event
{
public:
    explicit ReqDfViewEvent() {}
    EventType getType() const override { return EventType::e_reqDfV; }
};

#define SetCurrentView(x) eventSys.publish(x)
class ReqCurViewEvent : public Event
{
public:
    explicit ReqCurViewEvent() {}
    EventType getType() const override { return EventType::e_reqCurV; }
};

class attackEvent : public Event
{
public:
    explicit attackEvent(sf::Vector2f _mousePos, sf::RenderWindow* _win) : mousePos(_mousePos), win(_win) {}
    EventType getType() const override { return EventType::e_attack; }
    sf::Vector2f mousePos;
    sf::RenderWindow* win;
};

class equipEvent : public Event
{
public:
    explicit equipEvent(Weapon* _weapon = new Knife()) : weapon(_weapon) {}
    EventType getType() const override { return EventType::e_equip; }
    Weapon* weapon;
};

class openBagEvent : public Event
{
public:
    explicit openBagEvent() {}
    EventType getType() const override { return EventType::e_openBag; }
};

class boughtEvent : public Event
{
public:
    explicit boughtEvent(Weapon* _weapon) : weapon(_weapon) {}
    EventType getType() const override { return EventType::e_bought; }
    Weapon* weapon;
};

struct MouseState { bool left = 0, right = 0; sf::Vector2i pos; };
class mouseEvent : public Event
{
public:
    explicit mouseEvent(const MouseState& _mouseState) : MouseState(_mouseState) {}
    EventType getType() const override { return EventType::e_mouse; }
    MouseState MouseState;
};

struct DIR { bool up, down, left, right; };
class moveMentEvent : public Event
{
public:
    explicit moveMentEvent(const DIR& _dir, bool _isUIListening) : dir(_dir), isUIListening(_isUIListening){}
    EventType getType() const override { return EventType::e_moveMent; }

    DIR dir;
    bool isUIListening;
};

/**
 */
enum class UID{InputController, Shop, Bag};
class closeUIEvent : public Event
{
public:
    explicit closeUIEvent(UID _publisher, UID _subscriber) : publisher(_publisher), subscriber(_subscriber) {}
    EventType getType() const override { return EventType::e_closeUI; }
    UID publisher, subscriber;
};

class openProFileEvent : public Event
{
public:
    explicit openProFileEvent(){}
    EventType getType() const override { return EventType::e_openProFile;}
};

class openShopEvent : public Event
{
public:
    explicit openShopEvent(int _shopID) : shopID(_shopID) {}
    EventType getType() const override { return EventType::e_openShop; }

    int shopID;
};

class mapSwitchEvent : public Event
{
public:
    explicit mapSwitchEvent(int _nm) : newMapID(_nm) {}
    EventType getType() const override { return EventType::e_mapSwitch; }

    int newMapID;
};


