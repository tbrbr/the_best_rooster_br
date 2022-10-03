#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Galo.h"

#define FRAMERATE_LIMIT 60
#define println(x) std::cout << x << std::endl

using namespace sf;
using namespace Rooster;




int main(){

    RenderWindow* window = new RenderWindow(VideoMode(1280, 720), "TBRB");
    window->setFramerateLimit(FRAMERATE_LIMIT);

    Rooster::HitBox hb;
    Texture t;
    t.loadFromFile("sprites/galoSniper.png");

    Rooster::Galo galo(hb, 20, 20, 20, Rooster::state::STOPPED, t);

    int mouseX = 0;
    int mouseY = 0;

    while (window->isOpen()) {
        Event e;
        while (window->pollEvent(e)) {
            if (e.type == Event::Closed) {
                window->close();

            }

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::W) {
                    galo.animJump();
                }
                if (e.key.code == Keyboard::A) {
                    galo.setState(Rooster::RUNNING);
                    galo.facingRight = false;
                    galo.animRun();
                }
                if (e.key.code == Keyboard::D) {
                    galo.setState(Rooster::state::RUNNING);
                    galo.facingRight = true;
                    galo.animRun();
                }

            }

            if(e.type == Event::KeyReleased){
                if (e.key.code == Keyboard::A) {
                    galo.setState(Rooster::RUNNING);
                    galo.facingRight = false;
                    galo.animRun();
                }
                if (e.key.code == Keyboard::D) {
                }
            }
            if(e.type == Event::MouseMoved){
                mouseX = e.mouseMove.x;
                mouseY = e.mouseMove.y;
            }
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            galo.setState(Rooster::state::RUNNING);
            galo.facingRight = true;
            galo.animRun();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            galo.setState(Rooster::state::RUNNING);
            galo.facingRight = false;
            galo.animRun();
        } else {
            galo.setState(Rooster::state::STOPPED);
            galo.setHspeed(0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            galo.attacking = true;
        } else {
            galo.attacking = false;
        }


        galo.update(mouseX, mouseY);


        window->clear();
        RectangleShape fundo(Vector2f(1280, 720));
        fundo.setPosition(0,0);
        fundo.setFillColor(Color(100, 100, 100));

        window->draw(fundo);
        galo.show(*window);
        window->display();

    }



    return 0;
}
