#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Galo.h"

#define FRAMERATE_LIMIT 60
#define println(x) std::cout << x << std::endl

using namespace sf;
using namespace Rooster;

int main() {

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
                    galo.animRun();
                }
                if (e.key.code == Keyboard::D) {
                    galo.setState(Rooster::state::RUNNING + Rooster::RIGHT);
                    galo.animRun();
                }

            }

            if (e.type == Event::MouseMoved) {

                mouseX = e.mouseMove.x;
                mouseY = e.mouseMove.y;
            }

        }

        galo.update(mouseX, mouseY);


        window->clear();
        galo.show(*window);
        window->draw(galo.getSprite());
        window->display();

    }



    return 0;
}
