/*****************************************************************//**
 * \file   EventConfig.hpp
 * \brief  �Ҧ��ƥ��骺�w�q����b�o�Ӥ��Τ@�޲z�A
 *         �åѨƥ�޲z���ޥ�
 * 
 * \author YichenLin
 * \date   2024.11.10
 *********************************************************************/

#pragma once

#include "AllItems.hpp"

enum class EventType //�ƥ�uid
{
    e_mapSwitch,   //�a�Ϥ���
    e_openShop,    //�i�J�ө�
    e_openProFile, //���}�����T��
    e_closeUI,     //��������UI
    e_moveMent,    //���ʨƥ�(WSAD)
    e_mouse,       //�ƹ����A
    e_bought,      //�ʶR(�q�ө��ʶR�Ψ����^�I�])
    e_openBag,     //���}�I�]
    e_equip,       //�˳ƪ��~(�q�I�]�쨤��)
    e_attack,
    e_reqDfV,
    e_reqCurV
};

class Event //�ƥ����
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


