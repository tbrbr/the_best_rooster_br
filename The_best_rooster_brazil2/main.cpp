#include <iostream>
#include <SFML/Graphics.hpp>

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

    Rooster::Galo galo(hb, 20, 20, 20, Rooster::state::STOPPED, t);

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
                    galo.animRun();
                }
                if (e.key.code == Keyboard::D) {
                    galo.setState(Rooster::state::RUNNING + Rooster::RIGHT);
                    galo.animRun();
                }

            }

        }

        galo.update();

        window->clear();
        window->draw(galo.getSprite());
        window->display();

    }



    return 0;
}
