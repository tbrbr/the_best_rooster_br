#pragma once
#ifndef GALO_H_included
#define GALO_H_included



#include <SFML/Graphics.hpp>

using namespace sf;

#define PI 3.1415926563
#define G 9.81
#define Euler 2.718281

namespace Rooster {



    class Element {

    public:


        sf::Sprite sprite;
        Vector2f position;
        Vector2f center;

        Element(sf::Texture& text, Vector2i, int wid, int hei, int xPin, int yPin) {

            sprite.setTexture(text);
            sprite.setTextureRect(sf::IntRect(xTex, yTex, wid, hei));

            this->xPin = xPin - xTex;
            this->yPin = yPin - yTex;

            xOffset = 0;
            yOffset = 0;
            angleOffset = 0;

        }

        void show(sf::RenderWindow& window) {
            sprite.setPosition(x + xOffset - xPin + xAttach, y + yOffset - yPin + yAttach);
            sprite.setRotation(angle + angleOffset);

            sf::RectangleShape rectan(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
            rectan.setPosition(sprite.getPosition());
            rectan.setFillColor(Color(0, 0, 0, 0));
            rectan.setOutlineThickness(4);
            rectan.setOutlineColor(Color::White);
            window.draw(sprite);
            window.draw(rectan);

            sf::CircleShape circle(6);
            circle.setFillColor(Color::Red);
            circle.setPosition(x - xPin, y - yPin);
            window.draw(circle);
        }

        void update(float x, float y, float angle) {
            this->x = x;
            this->y = y;
            this->angle = angle;
        }
    };


    class Cock: Element{

        struct body {
            sf::Sprite sprite;
            Vector2f center;

        };

        struct head {
            sf::Sprite sprite;
            Vector2f center;
        };

        struct leftArm {
            sf::Sprite sprite;
            Vector2f center;
        };

        struct rightArm {
            sf::Sprite sprite;
            Vector2f center;
        };

        struct leftLeg {
            sf::Sprite sprite;
            Vector2f center;
        };

        struct rightLeg {
            sf::Sprite sprite;
            Vector2f center;
        };

        struct tail {
            sf::Sprite sprite;
            Vector2f center;
        };




    };






    enum state {
        STOPPED = 9,
        RUNNING,
        LOW_KICK,
        HIGH_KICK,
        SLAP,
        JUMP,
        JUMP_KICK,
        SPECIAL,
        DEFENDING,
        RIGHT

    };
    enum roosters {
        BOTAS,
        SNIPER,
        KALSA,
        PESTE_NEGRA,
        BRUXO
    };

    typedef struct {
        Vector2i xCenter;
        int radius;
    }HitBox;

    class Galo {
        HitBox hitbox;
        int hp;
        int id;
        float peso;
        int atk;
        int def;
        int speed;
        int estado;
        bool air;

        float hspeed;
        float vspeed;



        Sprite* sprite = new Sprite[9];
        RectangleShape r;



        std::vector<Element*> elementos;

    public:

        Galo(HitBox _hitbox, int atk, int def, int speed, int _state, Texture& _texture) {
            hitbox = _hitbox;
            this->atk = atk;
            this->def = def;
            this->speed = speed;
            this->estado = _state;
            this->peso = 2;
            this->air = false;
            this->hspeed = 0;
            this->vspeed = 0;
            r.setSize(Vector2f(20, 20));
            r.setPosition(400, 600);

            Element* galoBody = new Element(_texture, 26, 517, 479, 461, 250, 712);
            elementos.push_back(galoBody);

            Element* galoHead = new Element(_texture, 64, 38, 318, 434, 243, 420);
            galoHead->parentId = 0;
            galoHead->xAttach = -100 + (elementos.at(0)->sprite.getTextureRect().left + elementos.at(0)->xPin);
            galoHead->yAttach = -530 + (elementos.at(0)->sprite.getTextureRect().top + elementos.at(0)->yPin);

            elementos.push_back(galoHead);





        }

        RectangleShape getSprite() {
            return r;
        }
        void setState(state estado) {
            this->estado = estado;
        }
        void setState(int estado) {
            this->estado = estado;
        }
        void animJump() {

            if (!air) {
                this->vspeed += (peso * (-8)) / 2;
                air = true;
            }


        }
        void animRun() {
            if (this->estado - 18 >= 0)
                hspeed += 1;
            else {
                hspeed += -1;
            }

        }

        void show(sf::RenderWindow& window) {
            for (int i = 0; i < elementos.size(); i++) {
                elementos.at(i)->show(window);

            }
        }

        void inline update(int mx, int my) {

            this->vspeed += peso * G / 100;

            if (this->r.getPosition().y > 600) {
                this->vspeed = 0;
                this->r.setPosition(this->r.getPosition().x, 600);
                air = false;
            }

            this->r.move(this->hspeed, this->vspeed);


            elementos.at(0)->update(mx, my, 0);

            //elementos.at(1)->update(elementos.at(0)->x, elementos.at(0)->y, elementos.at(0)->angle);


        }
    };


}



#endif
