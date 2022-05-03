#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <time.h>
//using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game1", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    sf::Event ev;

    //Game loop
    while (window.isOpen())
    {
        //Event polling
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;

            }
        }
        //Update
        //window.clear(sf::Color(255, 255, 255, 255));
        window.clear(sf::Color::Blue);  //clear old frame
        //Render
        window.display();
    }

    //End of application
    system("pause");
    return 0;
}