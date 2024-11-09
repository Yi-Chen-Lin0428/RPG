#include "UI.hpp"

UI::UI(EventSystem& _eventSys) : eventSys(_eventSys)
{
    this->initUISprite();
    this->initBars();
}

UI::~UI()
{

}

void UI::dispUI(sf::RenderWindow& win)
{
    static ReqDfViewEvent reqDfVEve;
    static ReqCurViewEvent reqCurVEve;

    SetDefaultView(reqDfVEve);
    win.draw(HPBar);
    win.draw(MPBar);
    win.draw(levelBar);
    win.draw(UISprite);
    SetCurrentView(reqCurVEve);
}

void UI::dispHP()
{
    static sf::RectangleShape HPBar;

}

void UI::dispMP()
{

}

void UI::dispLevel()
{

}

void UI::dispMonsters()
{

}

void UI::dispBtns()
{

}

void UI::initButtons()
{
    if (btnList.empty()) //¨¾¤î­«½Æ«Ø¥ß
    {
        /*-------------------close button-------------------*/
        btnList.emplace_back(new Button("close", sf::Vector2f(832.f, 96.f), "./resources/buttons/buttons_sheet.png", 32, 32));

    }
}

void UI::deleteBtns()
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

void UI::initUISprite()
{
    if (!UITexture.loadFromFile("./resources/UI.png"))
    {
        std::cerr << "ERROR: UI texture load failed" << std::endl;
    }
    UISprite.setTexture(UITexture);
}

void UI::initBars()
{
    HPBar.setFillColor(sf::Color::Red);
    HPBar.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    HPBar.setPosition(BAR_FILLER_X_BASE_COORDINATE, BAR_FILLER_Y_BASE_COORDINATE);

    MPBar.setFillColor(sf::Color::Blue);
    MPBar.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    MPBar.setPosition(BAR_FILLER_X_BASE_COORDINATE, BAR_FILLER_Y_BASE_COORDINATE + BAR_Y_OFFSET * 2);

    levelBar.setFillColor(sf::Color::Yellow);
    levelBar.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    levelBar.setPosition(BAR_FILLER_X_BASE_COORDINATE, BAR_FILLER_Y_BASE_COORDINATE + BAR_Y_OFFSET * 4);
}
