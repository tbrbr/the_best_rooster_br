
#ifndef GALO_H_included
#define GALO_H_included



#include <iostream>


#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

#define PI 3.1415926563
#define G 9.81
#define Euler 2.718281





namespace Rooster {



    class Element{

        public:


        sf::Sprite sprite;

        Vector2f size;
        Vector2f texPos;
        Vector2f position;
        Vector2f center;
        Vector2f attach;

        Vector2f offset;

        int attachId = -1;

        float scl;

        float angle;

        float otherAngle = 0;

        Vector2f otherPos;

        Element(sf::Texture& text, int xTex, int yTex, int wid, int hei, int xPin, int yPin, int xAttach, int yAttach){

            sprite.setTexture(text);


            // Retangulo do sprite na textura
            texPos.x = xTex;
            texPos.y = yTex;
            size.x = wid;
            size.y = hei;

            sprite.setTextureRect(sf::IntRect(xTex, yTex, wid, hei));

            // Centro de rota��o do sprite
            center.x = xPin - xTex;
            center.y = yPin - yTex;

            sprite.setOrigin(center.x, center.y);


            // Relative to Center of part this is attached to
            attach.x = xAttach;
            attach.y = yAttach;

            // Angulo e escala
            angle = 0;
            scl = 0.25;

            offset.x = 0;
            offset.y = 0;




        }



        void show(sf::RenderWindow& window){
            sprite.setPosition(position);
            sprite.setRotation(angle+otherAngle);
            sprite.setScale(scl,scl);
            sprite.setOrigin(center.x, center.y);



            window.draw(sprite);

        }



        /// Updates element position based on the Part it's attached to
        void update(float otherX, float otherY, float otherAng){

            float fixAngle = 3.141592*otherAng/180;

            /// Calculando Posi��o atualizada
            position.x = offset.x + otherX + scl*(attach.x*cos(fixAngle) - attach.y*sin(fixAngle)) ;
            position.y = offset.y + otherY + scl*(attach.x*sin(fixAngle) + attach.y*cos(fixAngle));

            otherAngle = otherAng;

        }
    };








    enum state {
        STOPPED = 0,
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

        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        int frames = 0;



        Sprite * sprite = new Sprite[9];
        RectangleShape r;


        std::vector<int> elementDrawOrder;
        std::vector<Element*> elementos;

    public:

        bool facingRight = false;
        bool attacking = false;

        void addElement(sf::Texture& tex, float xTex, float yTex, float wid, float hei, float xCenter, float yCenter, float xAttach, float yAttach, int idAttach){

            float xAt = 0;
            float yAt = 0;
            if(idAttach != -1){
                xAt = xAttach - (elementos.at(idAttach)->texPos.x + elementos.at(idAttach)->center.x);
                yAt = yAttach - (elementos.at(idAttach)->texPos.y + elementos.at(idAttach)->center.y);
            } else {
                //cout << "Erro idAttach invalido" << endl;
            }

            Element* part = new Element(tex, xTex, yTex, wid, hei, xCenter, yCenter, xAt, yAt);
            part->attachId = idAttach;
            elementos.push_back(part);
        }

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



            /// Criando Partes do corpo
            addElement(_texture, 26, 517, 479, 461, 250, 712, 0, 0, -1); // Corpo

            addElement(_texture, 64, 38, 318, 434, 243, 420, 138, 595, 0); // Cabe�a

            addElement(_texture, 517, 565, 460, 517, 628, 834, 435, 824, 0); // Rabo

            addElement(_texture, 464, 264, 331, 233, 748, 380, 300, 670, 0); // AsaFrente

            addElement(_texture, 464, 264, 331, 233, 748, 380, 150, 700, 0); // AsaTr�s

            addElement(_texture, 100, 993, 144, 157, 202, 1015, 387, 930, 0); // Perna Frente

            addElement(_texture, 7, 1229, 260, 186, 173, 1242, 130, 1134, 5); // p� frente

            addElement(_texture, 100, 993, 144, 157, 202, 1015, 260, 910, 0); // Perna tr�s

            addElement(_texture, 7, 1229, 260, 186, 173, 1242, 130, 1134, 7); // p� tr�s


            elementDrawOrder.push_back(2);
            elementDrawOrder.push_back(4);
            elementDrawOrder.push_back(8);
            elementDrawOrder.push_back(7);
            elementDrawOrder.push_back(6);
            elementDrawOrder.push_back(5);
            elementDrawOrder.push_back(0);
            elementDrawOrder.push_back(1);
            elementDrawOrder.push_back(3);







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
                vspeed += (peso * (-8)) / 2;
                air = true;
            }


        }
        void animRun() {
            float acc = 0.5;
            if (facingRight){

                hspeed = (hspeed + acc) >  10 ?  10 : (hspeed + acc);
            }else {
                hspeed = (hspeed - acc) < -10 ? -10 : (hspeed - acc);
            }

        }

        void setHspeed(float spd){
            hspeed = spd;
        }

        void show(sf::RenderWindow& window){

            for(int i = 0; i < elementDrawOrder.size(); i++){
                elementos.at(elementDrawOrder.at(i))->show(window);
            }
        }

        void inline update(int mx, int my) {

            if(air){
                vspeed += peso * G/100;
            }



            if (r.getPosition().y > 600) {
                vspeed = 0;
                r.setPosition(r.getPosition().x, 600);
                air = false;
            }

            r.move(hspeed, vspeed);



            /// Anima��o das partes do corpo
            frames++;

            elementos.at(0)->angle += 0;
            elementos.at(0)->update(r.getPosition().x, r.getPosition().y, 0);

            elementos.at(2)->angle = sin(frames/200.f)*20;

            if(attacking){
                ArmSpinAngFase += 10;
                ArmSpinAngFase -= ((int)ArmSpinAngFase/360)*360;;
            } else {
                ArmSpinAngFase *= 0.9;
            }

            elementos.at(3)->angle = ArmSpinAngFase;
            elementos.at(3)->offset.y = sin(frames/200.f)*5;



            if(estado == RUNNING){
                legWalkAngFase += hspeed;

                legWalkAngFase -= ((int)legWalkAngFase/360)*360;

            } else {

                legWalkAngFase *= 0.8;
            }


            elementos.at(5)->angle = -sin(2*PI*legWalkAngFase/360)*60;
            elementos.at(7)->angle = sin(2*PI*legWalkAngFase/360)*60;




            for(int i = 1; i < elementos.size(); i++){

                Element* elem = elementos.at(elementos.at(i)->attachId);

                elementos.at(i)->update(elem->position.x, elem->position.y, elem->angle + elem->otherAngle);
            }


        }
    };


}



#endif
