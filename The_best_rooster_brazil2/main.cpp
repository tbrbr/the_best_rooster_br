#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <cmath>

using namespace sf;

#define FRAMERATE_LIMIT 60
#define G 9.81
#define PI 3.1415926563

#include "seraqueserver.h"
#include "Elementos.h"
#include "Galo.h"

using namespace Rooster;
using namespace std;

int main()
{
    UdpSocket socket;
    
    ConnectUDPSocket(socket, 2001);
    sf::IpAddress ip = IpAddress::getLocalAddress();

    unsigned short port = 2000;
    char data[100];

    cout << "Type your message";
    string message;
    getline(cin, message);
    SendData(socket, message, ip, port);
    receiveData(socket, data);
    cout << data;
    
    return 0;


    RenderWindow *window = new RenderWindow(VideoMode(1280, 720), "TBRB");
    window->setFramerateLimit(FRAMERATE_LIMIT);

    Rooster::HitBox hb;
    Texture t;
    t.loadFromFile("sprites/galoSniper.png");

    Rooster::Galo galo(hb, 20, 20, 20, Rooster::state::STOPPED, t);
    Rooster::Galo galo2(hb, 20, 20, 20, Rooster::state::STOPPED, t);

    int mouseX = 0;
    int mouseY = 0;

    while (window->isOpen())
    {
        Event e;
        while (window->pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window->close();
            }

            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::W)
                {
                    galo.animJump();
                }
                if (e.key.code == Keyboard::A)
                {
                    galo.setState(Rooster::RUNNING);
                    galo.facingRight = false;
                    galo.animRun();
                }
                if (e.key.code == Keyboard::D)
                {
                    galo.setState(Rooster::state::RUNNING);
                    galo.facingRight = true;
                    galo.animRun();
                }
            }

            if (e.type == Event::KeyReleased)
            {
                if (e.key.code == Keyboard::A)
                {
                    galo.setState(Rooster::RUNNING);
                    galo.facingRight = false;
                    galo.animRun();
                }
                if (e.key.code == Keyboard::D)
                {
                }
            }
            if (e.type == Event::MouseMoved)
            {
                mouseX = e.mouseMove.x;
                mouseY = e.mouseMove.y;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            galo.setState(Rooster::state::RUNNING);
            galo.facingRight = true;
            galo.animRun();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            galo.setState(Rooster::state::RUNNING);
            galo.facingRight = false;
            galo.animRun();
        }
        else
        {
            galo.setState(Rooster::state::STOPPED);
            galo.setHspeed(0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            galo2.setState(Rooster::state::RUNNING);
            galo2.facingRight = true;
            galo2.animRun();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            galo2.setState(Rooster::state::RUNNING);
            galo2.facingRight = false;
            galo2.animRun();
        }
        else
        {
            galo2.setState(Rooster::state::STOPPED);
            galo2.setHspeed(0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            galo.attacking = true;
        }
        else
        {
            galo.attacking = false;
        }

        galo.update(mouseX, mouseY);
        galo2.update(mouseX, mouseY);

        window->clear();
        RectangleShape fundo(Vector2f(1280, 720));
        fundo.setPosition(0, 0);
        fundo.setFillColor(Color(100, 100, 100));

        window->draw(fundo);
        galo.show(*window);
        galo2.show(*window);
        window->display();
    }

    return 0;
}
