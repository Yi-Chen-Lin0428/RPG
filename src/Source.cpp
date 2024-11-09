////////////////////////////////////////////////////////////
//                       CPP Headers                      //
////////////////////////////////////////////////////////////
#include <vector>
#include <iostream>
#include <cstring>

////////////////////////////////////////////////////////////
//                       SFML Headers                     //
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
//                      TMXLite Headers                   //
////////////////////////////////////////////////////////////
#include "SFMLOrthogonalLayer.hpp"
#include <tmxlite/Object.hpp>

////////////////////////////////////////////////////////////
//                       user Headers                     //
////////////////////////////////////////////////////////////
#include "Character.hpp"
#include "MapManager.hpp"
#include "EventSystem.hpp"
#include "Shop.hpp"
#include "InputController.hpp"
#include "Bag.hpp"   
#include "UI.hpp"
#include "ViewController.hpp"

#define CLOSE_WINDOW sfEvent.type     == sf::Event::Closed     || \
                     sfEvent.type     == sf::Event::KeyPressed && \
                     sfEvent.key.code == sf::Keyboard::Escape

using namespace std;
int getNumKey(sf::Event* eve);

const int viewWidth = 450;
const int viewHeight = 300;

int main()
{
    sf::RenderWindow window;

    EventSystem eventSystem;
    ViewController viewController(eventSystem, &window, viewWidth, viewHeight, 960, 640);
    InputController inputController(eventSystem);
    MapManager mapManager(eventSystem, 0);
    Character player(eventSystem, 0, "fuck u", 0);
    Shop shop(eventSystem);
    Bag inventory(eventSystem);
    UI ui(eventSystem);

    window.create(sf::VideoMode(MAP_WIDTH, MAP_HIGHTH), "RPG Game");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event sfEvent;
        while (window.pollEvent(sfEvent))
        {
            if (CLOSE_WINDOW)
            {
                window.close();
            }
        }
        
        inputController.inputScan(window);
        player.triggerHandler(mapManager.getTriggerObjs());
        player.update(mapManager.getCollObjs());
        mapManager.update(); 
        shop.update();
        inventory.update();
        viewController.updateView(player.getPos());

        window.clear();
        mapManager.draw(window);
        player.draw(window);
        ui.dispUI(window);
        shop.draw(window);
        inventory.draw(window);
        window.display();
    }

    return 0;
}

//unused
//int getNumKey(sf::Event* eve)
//{
//    static int num = 0;
//    if (eve->type == sf::Event::TextEntered)
//    {
//        if (eve->text.unicode >= 48 && eve->text.unicode <= 52)
//        {
//            num = static_cast<int>(eve->text.unicode) - 48;
//        }
//        return num;
//    }
//}
