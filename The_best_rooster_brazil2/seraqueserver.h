#ifndef SERAQUESERVER_H_INCLUDED
#define SERAQUESERVER_H_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;

typedef unsigned short us16;

/*void server(){
    cout << IpAddress::getLocalAddress();
    TcpListener listener;
    listener.listen(59000);
    TcpSocket client;
    listener.accept(client);
    char data[100] = "alcides: nota 10";
    client.send(data,100);

}

void client(){
    TcpSocket socket;
    IpAdress ip;
    us16 port = 59000;
    socket.connect(ip,port);
    char data[100] = "alcides: nota 10";
    size_t size;
    socket.receive(data,100,size);
    cout << data;
}
*/


#endif // SERAQUESERVER_H_INCLUDED
