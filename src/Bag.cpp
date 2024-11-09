#include "Bag.hpp"

Bag::Bag(EventSystem& _eventSys)
    : eventSys(_eventSys)
{
    /*------------------註冊call back函式------------------*/
    eventSys.subscribe<openBagEvent>(EventType::e_openBag, [this](openBagEvent& eve)
    {
        this->openBagEventHandler(eve);
    });
    eventSys.subscribe<mouseEvent>(EventType::e_mouse, [this](mouseEvent& eve)
    {
        this->mouseEventHandler(eve);
    });
    eventSys.subscribe<boughtEvent>(EventType::e_bought, [this](boughtEvent& eve)
    {
        this->boughtEventHandler(eve);
    });
    eventSys.subscribe<closeUIEvent>(EventType::e_closeUI, [this](closeUIEvent& eve)
    {
        this->closeUIEventHandler(eve);
    });
    /*----------------------------------------------------*/
    this->initBagUI();
}

Bag::~Bag()
{
    this->deleteBtns();
    this->deleteWeapons();
}

void Bag::update()
{
    if(isOpened)
    {
    /*----------------------------按鈕處理----------------------------*/
        this->initButtons();
        for (const auto& btn : btnList)
        {
            if (btn->getState(mouseState) == clicked)
            {
                static closeUIEvent closeUIEve(UID::Bag, UID::InputController);
                equipEvent equipEve(nullptr);
                Weapon* tmpWeapon;

                auto it = BagButtonMap.find(btn->getName());
                BagButtonType btnType = (it != BagButtonMap.end()) ? it->second : BagButtonType::Unknown;
                switch (btnType)
                {
                case BagButtonType::CloseBag:
                    isOpened = 0;
                    eventSys.publish(closeUIEve);
                    break;
                case BagButtonType::Equip:
                    if (weaponList.size() && selector <= weaponList.size() && selector) //確保不選空物品
                    {
                        tmpWeapon = weaponList[selector - 1];
                        equipEve = equipEvent(tmpWeapon);
                        eventSys.publish(equipEve);

                        weaponList[selector - 1] = tmpWeapon = nullptr;
                        delete textList[selector - 1];
                        weaponList.erase(weaponList.begin() + selector - 1);
                        textList.erase(textList.begin() + selector - 1);
                        selector = 0;
                    }
                    else
                    {
                        std::cerr << "Bag : no weapon to equip!!! " << std::endl;
                    }
                    break;
                case BagButtonType::Item1:
                    selector = 1;
                    break;
                case BagButtonType::Item2:
                    selector = 2;
                    break;
                case BagButtonType::Item3:
                    selector = 3;
                    break;
                case BagButtonType::Item4:
                    selector = 4;
                    break;
                case BagButtonType::Item5:
                    selector = 5;
                    break;
                case BagButtonType::Item6:
                    selector = 6;
                    break;
                case BagButtonType::Item7:
                    selector = 7;
                    break;
                case BagButtonType::Item8:
                    selector = 8;
                    break;
                case BagButtonType::Item9:
                    selector = 9;
                    break;
                default:
                    selector = 0;
                    std::cerr << "ERROR: Unknown button type" << std::endl;
                    break;
                }
            }
        }
        /*-----------------------------------------------------------------*/

        /*----------------------------物品信息處理--------------------------*/
        static int lastItemQty = 0;

        //更新文字
        if (weaponList.size() != lastItemQty || boughtEve) //當購買新物品或更換裝備
        {
            boughtEve = 0;
            for (auto text : textList)
            {
                delete text;
            }
            textList.clear();

            lastItemQty = static_cast<int>(weaponList.size());
            for (int i = 0; i < weaponList.size(); i++)
            {
                Text* tmpText = new Text();
                std::string tmpString = weaponList[i]->getName();
                tmpText->initText(48, tmpString, sf::Color::Black, 0);
                tmpText->setPos(dispPos[i].x + 70, dispPos[i].y);
                textList.emplace_back(tmpText);
            }
        }
        /*-----------------------------------------------------------------*/
    }
}

void Bag::draw(sf::RenderWindow& win)
{
    if (isOpened)
    {
        static ReqDfViewEvent reqDfVEve;
        static ReqCurViewEvent reqCurVEve;

        SetDefaultView(reqDfVEve);
        win.draw(UI);
        for (const auto& btn : btnList) //印UI
        {
            win.draw(btn->getSprite());
        }
        for (int i = 0; i < weaponList.size(); i++) //印武器
        {
            sf::Sprite tmpSprite = weaponList[i]->getSprite();
            tmpSprite.setScale(2, 2);
            tmpSprite.setPosition(dispPos[i].x, dispPos[i].y);
            win.draw(tmpSprite);
        }
        for (auto text : textList)
        {
            win.draw(text->text);
        }
        SetCurrentView(reqCurVEve);
    }
}

void Bag::addWeapon(Weapon* weapon)
{
    weaponList.emplace_back(weapon);
}

void Bag::sellWeapon(Weapon* weapon)
{

}

void Bag::initButtons()
{
    if (btnList.empty()) //防止重複建立
    {
        /*-------------------close button-------------------*/
        btnList.emplace_back(new Button("closeBag", sf::Vector2f(832.f, 96.f), "./resources/buttons/buttons_sheet.png", 32, 32));
        /*------------------equip button-----------------*/
        btnList.emplace_back(new Button("equip", sf::Vector2f(512.f, 480.f), "./resources/buttons/equip_button.png", 96, 32));
        /*--------------------next button-------------------*/
        btnList.emplace_back(new Button("next", sf::Vector2f(832.f, 320.f), "./resources/buttons/next.png", 32, 32, 1.5, 1.5));
        /*--------------------last button-------------------*/
        btnList.emplace_back(new Button("last", sf::Vector2f(80.f, 320.f), "./resources/buttons/last.png", 32, 32, 1.5, 1.5));
        /*-------------------item1 button-------------------*/
        btnList.emplace_back(new Button("item1", dispPos[0], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item2 button-------------------*/
        btnList.emplace_back(new Button("item2", dispPos[1], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item3 button-------------------*/
        btnList.emplace_back(new Button("item3", dispPos[2], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item4 button-------------------*/
        btnList.emplace_back(new Button("item4", dispPos[3], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item5 button-------------------*/
        btnList.emplace_back(new Button("item5", dispPos[4], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item6 button-------------------*/
        btnList.emplace_back(new Button("item6", dispPos[5], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item7 button-------------------*/
        btnList.emplace_back(new Button("item7", dispPos[6], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item8 button-------------------*/
        btnList.emplace_back(new Button("item8", dispPos[7], "./resources/buttons/selector.png", 192, 64));
        /*-------------------item9 button-------------------*/
        btnList.emplace_back(new Button("item9", dispPos[8], "./resources/buttons/selector.png", 192, 64));
    }
}

void Bag::initBagUI()
{
    if (!UITexture.loadFromFile("./resources/bagUI.png"))
    {
        std::cerr << "ERROR: bag ui load failed" << std::endl;
    }
    UI.setTexture(UITexture);
    UI.setPosition(0, 0);
}

void Bag::deleteBtns()
{
    for (auto btn : btnList)
    {
        delete btn;
    }
}

void Bag::deleteWeapons()
{
    if (weaponList.size())
    {
        for (auto weapon : weaponList)
        {
            delete weapon;
        }
    }
}

void Bag::openBagEventHandler(openBagEvent& eve)
{
    isOpened = 1;
}

void Bag::boughtEventHandler(boughtEvent& eve)
{
    boughtEve = 1;
    if (weaponList.size() < 9) //檢查容量
    {
        this->addWeapon(eve.weapon);
        eve.weapon = nullptr;
    }
    else
    {
        std::cout << "Bag : bag is full, you can't buy more items" << std::endl;
    }
}

void Bag::mouseEventHandler(mouseEvent& eve)
{
    mouseState = eve.MouseState;
}

void Bag::closeUIEventHandler(closeUIEvent& eve)
{
    if(eve.subscriber == UID::Bag) isOpened = 0;
}

std::array<sf::Vector2f, 9> dispPos = 
{
    sf::Vector2f(160.f, 192.f),
    sf::Vector2f(384.f, 192.f),
    sf::Vector2f(608.f, 192.f),
    sf::Vector2f(160.f, 288.f),
    sf::Vector2f(384.f, 288.f),
    sf::Vector2f(608.f, 288.f),
    sf::Vector2f(160.f, 384.f),
    sf::Vector2f(384.f, 384.f),
    sf::Vector2f(608.f, 384.f)
};