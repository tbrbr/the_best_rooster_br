
#ifndef GALO_H_included
#define GALO_H_included

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

#define PI 3.1415926563
#define G 9.81
#define Euler 2.718281



namespace Rooster
{

/* a element is a small part of a rooster or any caracther available
that way the animations will be smoother and easy to make for any rooster*/

class Element
{

public:


    sf::Sprite sprite;

    Vector2f size;
    Vector2f texPos;
    Vector2f position;
    Vector2f center;
    Vector2f attach;

    Vector2f offset;

    int attachId = -1;

    Vector2f scl;

    float angle;

    float otherAngle = 0;

    Vector2f otherPos;

    Element(sf::Texture& text, int xTex, int yTex, int wid, int hei, int xPin, int yPin, int xAttach, int yAttach)
    {

        sprite.setTexture(text);


        // Retangulo do sprite na textura
        texPos.x = xTex;
        texPos.y = yTex;
        size.x = wid;
        size.y = hei;

        sprite.setTextureRect(sf::IntRect(xTex, yTex, wid, hei));

        // Centro de rotação do sprite
        center.x = xPin - xTex;
        center.y = yPin - yTex;

        sprite.setOrigin(center.x, center.y);


        // Relative to Center of part this is attached to
        attach.x = xAttach;
        attach.y = yAttach;

        // Angulo e escala
        angle = 0;
        scl.x = 0.25;
        scl.y = 0.25;

        offset.x = 0;
        offset.y = 0;




    }



    void show(sf::RenderWindow& window)
    {
        sprite.setPosition(position);
        sprite.setRotation(angle+otherAngle);
        sprite.setScale(scl.x,scl.y);
        sprite.setOrigin(center.x, center.y);
        window.draw(sprite);

    }



    /// Updates element position based on the Part it's attached to
    void update(float otherX, float otherY, float otherAng)
    {

        float fixAngle = 3.141592*otherAng/180;

        /// Calculating actualized position...
        position.x = offset.x + otherX + scl.x*(attach.x*cos(fixAngle) - attach.y*sin(fixAngle)) ;
        position.y = offset.y + otherY + scl.y*(attach.x*sin(fixAngle) + attach.y*cos(fixAngle));

        otherAngle = otherAng;

    }
};



enum state
{
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
enum roosters
{
    BOTAS,
    SNIPER,
    KALSA,
    PESTE_NEGRA,
    BRUXO
};

enum bodyParts{
     CORPO,
     CABECA,
     RABO,
     ASA_FRENTE,
     ASA_ATRAS,
     PERNA_FRENTE,
     PE_FRENTE,
     PERNA_ATRAS,
     PE_ATRAS

};

typedef struct
{
    Vector2i xCenter;
    int radius;
} HitBox;

class Galo
{
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
    float Arm2SpinAngFase = 0;

    int frames = 0;

    Sprite * sprite = new Sprite[9];
    RectangleShape r;


    std::vector<int> elementDrawOrder;
    std::vector<Element*> elementos;

public:

    bool facingRight = false;
    bool attacking = false;

    void addElement(sf::Texture& tex, float xTex, float yTex, float wid,
                    float hei, float xCenter, float yCenter, float xAttach,
                    float yAttach, int idAttach){

        float xAt = 0;
        float yAt = 0;
        if(idAttach != -1)
        {
            xAt = xAttach - (elementos.at(idAttach)->texPos.x + elementos.at(idAttach)->center.x);
            yAt = yAttach - (elementos.at(idAttach)->texPos.y + elementos.at(idAttach)->center.y);
        }

        Element* part = new Element(tex, xTex, yTex, wid, hei, xCenter, yCenter, xAt, yAt);
        part->attachId = idAttach;
        elementos.push_back(part);
    }

    Galo(HitBox _hitbox, int atk, int def, int speed, int _state, Texture& _texture)
    {
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

        addElement(_texture, 64, 38, 318, 434, 243, 420, 138, 595, 0); // Cabeça

        addElement(_texture, 517, 565, 460, 517, 628, 834, 435, 824, 0); // Rabo

        addElement(_texture, 464, 264, 331, 233, 748, 380, 300, 670, 0); // AsaFrente

        addElement(_texture, 464, 264, 331, 233, 748, 380, 150, 700, 0); // AsaTrás

        addElement(_texture, 100, 993, 144, 157, 202, 1015, 387, 930, 0); // Perna Frente

        addElement(_texture, 7, 1229, 260, 186, 173, 1242, 130, 1134, 5); // pé frente

        addElement(_texture, 100, 993, 144, 157, 202, 1015, 260, 910, 0); // Perna trás

        addElement(_texture, 7, 1229, 260, 186, 173, 1242, 130, 1134, 7); // pé trás


        elementDrawOrder.push_back(RABO);
        elementDrawOrder.push_back(ASA_ATRAS);
        elementDrawOrder.push_back(PE_ATRAS);
        elementDrawOrder.push_back(PERNA_ATRAS);
        elementDrawOrder.push_back(PE_FRENTE);
        elementDrawOrder.push_back(PERNA_FRENTE);
        elementDrawOrder.push_back(CORPO);
        elementDrawOrder.push_back(CABECA);
        elementDrawOrder.push_back(ASA_FRENTE);

    }

    RectangleShape getSprite()
    {
        return r;
    }
    void setState(state estado)
    {
        this->estado = estado;
    }
    void setState(int estado)
    {
        this->estado = estado;
    }
    void animJump()
    {
        if (!air)
        {
            vspeed += (peso * (-8)) / 2;
            air = true;
        }
    }
    void animRun()
    {
        float acc = 0.5;

        if (facingRight)
        {
            hspeed = (hspeed + acc) >  10 ?  10 : (hspeed + acc);
            for(int i = 0; i < elementos.size(); i ++){
                elementos.at(i)->scl.x = -0.25;

            }
        }
        else
        {
            hspeed = (hspeed - acc) < -10 ? -10 : (hspeed - acc);
            for(int i = 0; i < elementos.size(); i ++){
                elementos.at(i)->scl.x = 0.25;

            }

        }

    }

    void setHspeed(float spd)
    {
        hspeed = spd;
    }

    void show(sf::RenderWindow& window)
    {

        for(int i = 0; i < elementDrawOrder.size(); i++)
        {
            elementos.at(elementDrawOrder.at(i))->show(window);
        }
    }

    void inline update(int mx, int my)
    {

        if(air)
        {
            vspeed += peso * G/100;
        }

        if (r.getPosition().y > 600)
        {
            vspeed = 0;
            r.setPosition(r.getPosition().x, 600);
            air = false;
        }

        r.move(hspeed, vspeed);

        /// Animação das partes do corpo

        //these parts moves all the time to create weather like animations
        frames++;

        elementos.at(CORPO)->angle += 0;
        elementos.at(CORPO)->update(r.getPosition().x, r.getPosition().y, 0);

        elementos.at(RABO)->angle = sin(frames/200.f)*20;

        /******************************************************************/

        if(attacking)
        {
            ArmSpinAngFase += 10;
            ArmSpinAngFase -= ((int)ArmSpinAngFase/360)*360;
        }
        else
        {
            ArmSpinAngFase *= 0.9;
            Arm2SpinAngFase *= 0.9;
        }

        //jump animation
        if(air){
            ArmSpinAngFase = (vspeed/8) * 45;
            Arm2SpinAngFase =(vspeed/8) * 45;

            elementos.at(PERNA_FRENTE)->attach.y += vspeed/2;
            elementos.at(PE_FRENTE)->angle += vspeed/20;
            elementos.at(PERNA_ATRAS)->attach.y += vspeed/4;
            elementos.at(PE_ATRAS)->angle += vspeed/20;
        }

        elementos.at(ASA_FRENTE)->angle = ArmSpinAngFase;
        elementos.at(ASA_FRENTE)->offset.y = sin(frames/200.f)*5;
        elementos.at(ASA_ATRAS)->angle = Arm2SpinAngFase;
        elementos.at(ASA_ATRAS)->offset.y = sin(frames/200.f)*5;

        //running animation
        if(estado == RUNNING)
        {
            legWalkAngFase += hspeed;
            legWalkAngFase -= ((int)legWalkAngFase/360)*360;
        }
        else
        {
            legWalkAngFase *= 0.8;
        }


        elementos.at(PERNA_FRENTE)->angle = sin(2*PI*legWalkAngFase/360)*60;
        elementos.at(PERNA_ATRAS)->angle = -sin(2*PI*legWalkAngFase/360)*60;


        for(int i = 1; i < elementos.size(); i++)
        {

            Element* elem = elementos.at(elementos.at(i)->attachId);
            elementos.at(i)->update(elem->position.x, elem->position.y, elem->angle + elem->otherAngle);
        }


    }
};


}



#endif
