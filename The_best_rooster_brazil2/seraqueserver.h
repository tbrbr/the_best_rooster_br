#ifndef SERAQUESERVER_H_INCLUDED
#define SERAQUESERVER_H_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
using namespace sf;

typedef unsigned short us16;

void ConnectUDPSocket(UdpSocket & socket, us16 port){
    if (socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "Failz\n";
    }
}

void receiveData(UdpSocket & socket, char data[]){
    sf::IpAddress sender;
    size_t received;
    us16 port;

    if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
    {
        std::cout << "Falha na comunicação com o servidor" << std::endl;
        return;
    }

    std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
}


void SendData(UdpSocket & socket, std::string & message, IpAddress & ip, us16 port){

    if (socket.send(message.c_str(), message.size() + 1, ip, port) != sf::Socket::Done)
    {
        std::cout << "Falha na comunicação com o servidor" << std::endl;
    }
}


#endif // SERAQUESERVER_H_INCLUDED
