#pragma once
#ifndef GALO_H_included
#define GALO_H_included

using namespace sf;

#include <SFML/Graphics.hpp>
#define PI 3.1415926563
#define G 9.81
#define Euler 2.718281

namespace Rooster {

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

        Sprite * sprite = new Sprite[9];
        RectangleShape r;

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
                hspeed += - 1;
            }

        }

        void inline update() {

            this->vspeed += peso * G/100;

            if (this->r.getPosition().y > 600) {
                this->vspeed = 0;
                this->r.setPosition(this->r.getPosition().x, 600);
                air = false;
            }

            this->r.move(this->hspeed, this->vspeed);


        }
    };


}



#endif
