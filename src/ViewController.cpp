#include "ViewController.hpp"


ViewController::ViewController(EventSystem& _eventSys, sf::RenderWindow* _win, int V_width, int V_height, int M_width, int M_height)
    :eventSys(_eventSys), win(_win), vW(V_width), vH(V_height), mW(M_width), mH(M_height)
{
    /*------------------µù¥Ucall back¨ç¦¡------------------*/
	eventSys.subscribe<ReqDfViewEvent>(EventType::e_reqDfV, [this](ReqDfViewEvent& eve)
	{
		this->reqDfViewEventHandler(eve);
	});
    eventSys.subscribe<ReqCurViewEvent>(EventType::e_reqCurV, [this](ReqCurViewEvent& eve)
	{
		this->reqCurViewEventHandler(eve);
	});
	/*----------------------------------------------------*/
    view = sf::View(sf::FloatRect(0, 0, (float)V_width, (float)V_height));
}

ViewController::~ViewController()
{
    //delete win;
}

void ViewController::updateView(sf::Vector2f centerPos)
{
    view.setCenter(limitViewPos(centerPos));
    win->setView(view);
}

sf::Vector2f ViewController::limitViewPos(sf::Vector2f pos)
{
    pos += sf::Vector2f(16.f, 16.f);

    float viewX = std::max(vW / 2.f, std::min(pos.x, mW - vW / 2.f));
    float viewY = std::max(vH / 2.f, std::min(pos.y, mH - vH / 2.f));
    return sf::Vector2f(viewX, viewY);
}

void ViewController::reqDfViewEventHandler(ReqDfViewEvent& eve)
{
    win->setView(win->getDefaultView());
}

void ViewController::reqCurViewEventHandler(ReqCurViewEvent& eve)
{
    win->setView(view);
}
