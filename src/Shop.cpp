#include "Shop.hpp"


Shop::Shop(EventSystem& _eventSys)
    : isOpened(0), shopID(0), eventSys(_eventSys)
{
    /*------------------註冊call back函式------------------*/
    eventSys.subscribe<openShopEvent>(EventType::e_openShop, [this](openShopEvent& eve)
    {
        this->openShopEventHandler(eve);
    });
    eventSys.subscribe<moveMentEvent>(EventType::e_moveMent, [this](moveMentEvent& eve)
    {
        this->moveMentEventHandler(eve);
    });
    eventSys.subscribe<mouseEvent>(EventType::e_mouse, [this](mouseEvent& eve)
    {
        this->mouseEventHandler(eve);
    });
    eventSys.subscribe<closeUIEvent>(EventType::e_closeUI, [this](closeUIEvent& eve)
    {
        this->closeUIEventHandler(eve);
    });
    /*----------------------------------------------------*/
    UI.setPosition(sf::Vector2f(0.f, 0.f));
    initTextPos();
    getShopName[0] = "Weapon";
    getShopName[1] = "Armor";
    getShopName[2] = "Potion";
    this->initShopData();
}

Shop::~Shop()
{
    this->deleteBtns();
    this->deleteWeapons();
} 

void Shop::update()
{
    if (isOpened)
    {
        static closeUIEvent closeUIEve(UID::Shop, UID::InputController);
        static int lastShopID;
        /*----------------------------按鈕處理----------------------------*/
        this->initButtons();
        for (const auto& btn : btnList)
        {
            if (btn->getState(mouseState) == clicked)
            {
                auto it = buttonMap.find(btn->getName());
                ButtonType btnType = (it != buttonMap.end()) ? it->second : ButtonType::Unknown;
                switch (btnType)
                {
                case ButtonType::Close:
                    isOpened = 0;
                    eventSys.publish(closeUIEve);                  
                    break;
                case ButtonType::Purchase:
                    this->purchaseHandler();
                    break;
                case ButtonType::Next:
                    this->switchShop(1);
                    break;
                case ButtonType::Last:
                    this->switchShop(0);
                    break;
                case ButtonType::Item1:
                    shoppingCart = 1;
                    break;
                case ButtonType::Item2:
                    shoppingCart = 2;
                    break;
                case ButtonType::Item3:
                    shoppingCart = 3;
                    break;
                case ButtonType::Item4:
                    shoppingCart = 4;
                    break;
                case ButtonType::Item5:
                    shoppingCart = 5;
                    break;
                case ButtonType::Item6:
                    shoppingCart = 6;
                    break;
                case ButtonType::Item7:
                    shoppingCart = 7;
                    break;
                case ButtonType::Item8:
                    shoppingCart = 8;
                    break;
                default:
                    shoppingCart = 1;
                    std::cerr << "ERROR: Unknown button type" << std::endl;
                    break;
                }
                this->dispShoppingCart();
            }
        }
        /*----------------------------按鈕處理----------------------------*/
    }
    else
    {
        this->deleteBtns();
    }
}
 
void Shop::draw(sf::RenderWindow& win)
{
    if (isOpened)
    {
        static ReqDfViewEvent reqDfVEve;
        static ReqCurViewEvent reqCurVEve;

        SetDefaultView(reqDfVEve);
        win.draw(UI);
        for (const auto& btn : btnList)
        {
            win.draw(btn->getSprite());
        }
        if (shoppingCart && shopID != 3)
        {
            win.draw(tmpSprite);
            win.draw(itemName.text);
            win.draw(itemWeight.text);
            win.draw(itemDamage.text);
            win.draw(itemDefense.text);
            win.draw(itemPrice.text);
        }   
        SetCurrentView(reqCurVEve);
    }
}

void Shop::purchaseHandler()
{
    boughtEvent boughtEve(nullptr);
    if (!shoppingCart)
    {
        std::cout << "SHOP: 你是買不起嗎? 還沒選東西 " << std::endl;
    }
    else if (shopID == 1) //武器商店
    {
        if (weaponList[shoppingCart - 1]->getName() != "none") //檢查庫存
        {
            boughtEve = boughtEvent(weaponList[shoppingCart - 1]->clone());
            eventSys.publish(boughtEve);
            std::cout << "SHOP: purchase item " << weaponList[shoppingCart - 1]->getName() << std::endl;
        }
        else
        {
            std::cout << "SHOP: Out of stock!!! " << std::endl;
        }
    }
    else if (shopID == 2) //防具商店
    {

    }
    else
    {
        //開發中...
    }
}

void Shop::dispShoppingCart()
{
    if (shoppingCart)
    {
        switch (shopID) //處理要顯示的商品資訊
        {
        case 1:
            tmpSprite = weaponList[shoppingCart - 1]->getSprite();
            tmpSprite.setScale(3, 3);
            tmpSprite.setPosition(sf::Vector2f(672.f, 160.f)); //調整到顯示區

            itemName.initText(TEXT_SIZE, weaponList[shoppingCart - 1]->getName(), sf::Color::Black, 0);
            itemWeight.initText(TEXT_SIZE, weaponList[shoppingCart - 1]->getWeight(), sf::Color::Black, 0);
            itemDamage.initText(TEXT_SIZE, weaponList[shoppingCart - 1]->getDamage(), sf::Color::Black, 0);
            itemPrice.initText(TEXT_SIZE, weaponList[shoppingCart - 1]->getPrice(), sf::Color::Black, 0);
            itemDefense.initText(0, "");
            break;
        case 2:
            itemName.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            itemWeight.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            itemDamage.initText(0, "", sf::Color::Black, 0);
            itemPrice.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            itemDefense.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            break;
        case 3:
            itemName.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            itemWeight.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            itemDamage.initText(0, "", sf::Color::Black, 0);
            itemPrice.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            itemDefense.initText(TEXT_SIZE, "", sf::Color::Black, 0);
            break;
        default:
            break;
        }
    }
}

void Shop::switchShop(bool _dir)
{
    shopID += _dir == 1 ? 1 : -1;
    if (shopID > 3) shopID = 1;
    if (shopID < 1) shopID = 3;
    std::cout << "SHOP: switch to " << getShopName[shopID - 1] << " shop" << std::endl;
    this->initTexture("./resources/shop" + std::to_string(shopID) + "UI.png");
}

void Shop::initTextPos()
{
    itemName.setPos(695, 290);
    itemWeight.setPos(695, 328);
    itemDamage.setPos(695, 366);
    itemDefense.setPos(695, 366);
    itemPrice.setPos(695, 402);
}
    
void Shop::initTexture(std::string _UITexture)
{
    if (!UITexture.loadFromFile(_UITexture))
    {
        std::cerr << "ERROR: shopUI Texture load failed! " << std::endl;
    }
    UI.setTexture(UITexture);
}

/**
 * 按鈕編號:
 *   1  5
 *   2  6
 *   3  7
 *   4  8
 */
void Shop::initButtons()
{
    if (btnList.empty()) //防止重複建立
    {
        /*-------------------close button-------------------*/
        btnList.emplace_back(new Button("close", sf::Vector2f(832.f, 96.f), "./resources/buttons/buttons_sheet.png", 32, 32));
        /*------------------purchase button-----------------*/
        btnList.emplace_back(new Button("purchase", sf::Vector2f(680.f, 492.f), "./resources/buttons/button2.png", 96, 32));
        /*--------------------next button-------------------*/
        btnList.emplace_back(new Button("next", sf::Vector2f(832.f, 320.f), "./resources/buttons/next.png", 32, 32, 1.5, 1.5));
        /*--------------------last button-------------------*/
        btnList.emplace_back(new Button("last", sf::Vector2f(80.f, 320.f), "./resources/buttons/last.png", 32, 32, 1.5, 1.5));
        /*-------------------item1 button-------------------*/
        btnList.emplace_back(new Button("item1", sf::Vector2f(160.f, 160.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item2 button-------------------*/
        btnList.emplace_back(new Button("item2", sf::Vector2f(160.f, 256.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item3 button-------------------*/
        btnList.emplace_back(new Button("item3", sf::Vector2f(160.f, 352.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item4 button-------------------*/
        btnList.emplace_back(new Button("item4", sf::Vector2f(160.f, 448.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item5 button-------------------*/
        btnList.emplace_back(new Button("item5", sf::Vector2f(384.f, 160.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item6 button-------------------*/
        btnList.emplace_back(new Button("item6", sf::Vector2f(384.f, 256.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item7 button-------------------*/
        btnList.emplace_back(new Button("item7", sf::Vector2f(384.f, 352.f), "./resources/buttons/selector.png", 192, 64));
        /*-------------------item8 button-------------------*/
       btnList.emplace_back(new Button("item8", sf::Vector2f(384.f, 448.f), "./resources/buttons/selector.png", 192, 64));
       //std::cout << "SHOP: button init successed" << std::endl;
    }
}


void Shop::initShopData() //加入商品
{
    /*-------------------------武器商店-------------------------*/
    weaponList.emplace_back(new Ax());
    weaponList.emplace_back(new Pistol());
    weaponList.emplace_back(new Rifle());
    weaponList.emplace_back(new None());
    weaponList.emplace_back(new Knife());
    weaponList.emplace_back(new Pump());
    weaponList.emplace_back(new None());
    weaponList.emplace_back(new None());

    /*-------------------------防具商店-------------------------*/
}

void Shop::deleteBtns()
{
    if (btnList.size())
    {
        for (auto btn : btnList)
        {
            delete btn;
        }
        btnList.clear();
    }
}

void Shop::deleteWeapons()
{
    if (weaponList.size())
    {
        for (auto weapon : weaponList)
        {
            delete weapon;
        }
        weaponList.clear();
    }
}

void Shop::mouseEventHandler(mouseEvent& eve)
{
    mouseState = eve.MouseState;
}

void Shop::moveMentEventHandler(moveMentEvent& eve)
{
    dir = eve.dir;
}

void Shop::openShopEventHandler(openShopEvent& eve)
{
    isOpened = 1;
    shopID = eve.shopID;

    if (!shopID && shopID > 3) { std::cerr << "ERROR: shop 0 doesn't exist" << std::endl; }
    else{std::cout << "INFO: open  " << getShopName[shopID - 1] << " shop " << std::endl; }
    this->initTexture("./resources/shop" + std::to_string(shopID) + "UI.png");

}

void Shop::closeUIEventHandler(closeUIEvent& eve)
{
    isOpened = 0;
}
