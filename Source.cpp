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

#define DEBUG       
#define CLOSE_WINDOW event.type     == sf::Event::Closed     || \
                     event.type     == sf::Event::KeyPressed && \
                     event.key.code == sf::Keyboard::Escape

using namespace std;
int getNumKey(sf::Event* eve);

int main()
{
    int mapID = 0;
    MapManager mapManager(mapID);
    Character player(0);

    sf::RenderWindow window;
    sf::View view(sf::FloatRect(0, 0, 384, 256)); // 設定視圖大小
    window.create(sf::VideoMode(MAP_WIDTH, MAP_HIGHTH), "Map Test");
    window.setFramerateLimit(60);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (CLOSE_WINDOW)
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) //debug mode改地圖
            {
                mapID = getNumKey(&event);
            }
        }
        
        //cout << "collison obj size = " << mapManager.getCollObjs().size() << endl;
        player.update(mapManager.getCollObjs());
        mapManager.update(mapID, {0, 0});

        view.setCenter(player.getPos() + sf::Vector2f(16.f, 16.f));
        window.setView(view);
        window.clear(sf::Color::Black);

        mapManager.draw(window, view);
        player.draw(window);
        window.display();
    }

    return 0;
}


int getNumKey(sf::Event* eve)
{
    static int num = 0;
    if (eve->type == sf::Event::TextEntered)
    {
        if (eve->text.unicode >= 48 && eve->text.unicode <= 52)
        {
            num = static_cast<int>(eve->text.unicode) - 48;
        }
        return num;
    }
    else{}
}
