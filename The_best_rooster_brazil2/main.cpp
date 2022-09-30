#include <iostream>
#include <SFML/Graphics.hpp>


using namespace sf;


int main()
{
    err().rdbuf(NULL);

    RenderWindow mainWindow(VideoMode(800, 600), "TBRB");
    mainWindow.setFramerateLimit(60);



    while(mainWindow.isOpen()) {

        Event e;

        while(mainWindow.pollEvent(e)) {

            if(e.type == Event::Closed){
                mainWindow.close();
            }
        }

        mainWindow.clear();
        mainWindow.display();
    }


    return 0;
}
