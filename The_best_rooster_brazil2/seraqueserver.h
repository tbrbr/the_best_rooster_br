#ifndef SERAQUESERVER_H_INCLUDED
#define SERAQUESERVER_H_INCLUDED

#include <SFML/Network.hpp>

void bindingUdp() {

    UdpSocket socket;

    IpAddress ip = IpAddress::getLocalAddress();

    if (socket.bind(Socket::AnyPort) != Socket::Done) {
        std::cout << "moiou" << std::endl;
    }
    unsigned short port = socket.getLocalPort();
}

void send(char data[],int sizeData){

    UdpSocket socket;
    unsigned short port = socket.getLocalPort();
    char data1[100] = "mota nao tem a senha";

    IpAddress recipient = sf::IpAddress::Broadcast;
    if (socket.send(data, 100, recipient, port) != Socket::Done) {
        // error...
    }

}

void receive(char data[]){
    UdpSocket socket;
    sf::IpAddress sender;
    unsigned short port;
    //    if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
    //{
        // error...
    //}
    //std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
}





#endif // SERAQUESERVER_H_INCLUDED
