#include "InputController.hpp"


InputController::InputController(EventSystem& _eventSys)
    : eventSys(_eventSys), dir()
{
    /*------------------註冊call back函式------------------*/
    eventSys.subscribe<openProFileEvent>(EventType::e_openProFile, [this](openProFileEvent& eve)
    {
        this->openProFileEventHandler(eve);
    });
    eventSys.subscribe<openShopEvent>(EventType::e_openShop, [this](openShopEvent& eve)
    {
        this->openShopEventHandler(eve);
    });
    eventSys.subscribe<closeUIEvent>(EventType::e_closeUI, [this](closeUIEvent& eve)
    {
        this->closeUIEventHandler(eve);
    });
    /*-----------------------------------------------------*/

    scanSpd.restart();
}

InputController::~InputController(){}

void InputController::inputScan(sf::RenderWindow& win)
{
    if (scanSpd.getElapsedTime().asMilliseconds() < 10) 
    {
        return;
    }
    if (currentS != nextS) { currentS = nextS; }
    scanSpd.restart();

    /*------------------建立事件實體------------------*/
    DIR dir;
    MouseState mouseState;

    static moveMentEvent moveMentEve(dir, 0);
    static mouseEvent mouseEve(mouseState);
    static attackEvent  attackEve(sf::Vector2f(0.f, 0.f), nullptr);
    /*-----------------------------------------------*/

    /*-----------方向鍵檢測-----------*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { dir.up    = 1; } else { dir.up    = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { dir.down  = 1; } else { dir.down  = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { dir.left  = 1; } else { dir.left  = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { dir.right = 1; } else { dir.right = 0; }
    /*-------------------------------*/

    /*-----------功能鍵檢測-----------*/
    this->handleKeyB(0);
    this->handleKeyH(0);
    /*-------------------------------*/

    /*------------滑鼠檢測------------*/
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  { mouseState.left  = 1; } else{ mouseState.left  = 0; }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) { mouseState.right = 1; } else{ mouseState.right = 0; }
    mouseState.pos = sf::Mouse::getPosition(win);
    /*-------------------------------*/

    switch (currentS) //狀態處理
    {
        case character:  
            moveMentEve = moveMentEvent(dir, 0);
            attackEve = attackEvent(static_cast<sf::Vector2f>(mouseState.pos), &win);
            if (mouseState.left) //發布攻擊事件，由角色處理
            { 
                this->publish(attackEve); 
            }
            break;
        case shopUI:
            moveMentEve = moveMentEvent(dir, 1); 
            break;
        case bagUI:
            moveMentEve = moveMentEvent(dir, 1);
            break;
        case proFileUI:
            moveMentEve = moveMentEvent(dir, 1);
            break;
        default:
            break;
    }
    this->publish(moveMentEve);
    static MouseState lastMouseState;

    if (mouseState.left  != lastMouseState.left  ||
        mouseState.right != lastMouseState.right ||
        mouseState.pos.x != lastMouseState.pos.x ||
        mouseState.pos.y != lastMouseState.pos.y)
    {
        mouseEve = mouseEvent(mouseState);
        this->publish(mouseEve);
    }
}

void InputController::publish(Event& eve)
{
    eventSys.publish(eve);
}

/*------------------功能鍵處理------------------*/
void InputController::handleKeyH(bool closeBtnSync)
{
    static bool cs = 0;
    static openShopEvent openShopEve(1); //默認進入武器商店
    static closeUIEvent closeUIEve(UID::InputController, UID::Shop);

    cs = (nextS == shopUI);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) || closeBtnSync)
    {
        cs = (closeBtnSync ? 0 : !cs);
        if (cs)
        {
            nextS = shopUI;
            eventSys.publish(openShopEve);
        }
        else
        {
            nextS = character;
            eventSys.publish(closeUIEve);
            std::cout << "INFO: shop is closed" << std::endl;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {};
    }
}

void InputController::handleKeyB(bool closeBtnSync)
{
    static bool cs = 0;
    static openBagEvent openBagEve;
    static closeUIEvent closeUIEve(UID::InputController, UID::Bag);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) || closeBtnSync)
    {
        cs = !cs;
        if (cs)
        {
            nextS = bagUI;
            eventSys.publish(openBagEve);
            std::cout << "INFO: bag is opened" << std::endl;
        }
        else
        {
            nextS = character;
            eventSys.publish(closeUIEve);
            std::cout << "INFO: bag is closed" << std::endl;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {};
    }
}


/*------------------狀態轉移------------------*/

void InputController::openProFileEventHandler(openProFileEvent& eve)
{
    nextS = proFileUI;
}

void InputController::openShopEventHandler(openShopEvent& eve)
{
    nextS = shopUI;
}

void InputController::closeUIEventHandler(closeUIEvent& eve)
{
    //nextS = character;
    if(eve.publisher == UID::Bag)  this->handleKeyB(1);
    if (eve.publisher == UID::Shop) this->handleKeyH(1);
}

