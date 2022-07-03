#include "server.hpp"

namespace sv
{

bool Shift::compare(Shift a, Shift b)
{
    return a.date > b.date;
}

Server::Server()
{
    // connect to server
}

Server::~Server()
{
    // disconnect from server
}

void Server::saveShifts(std::vector<Shift> shifts)
{
    // write shifts to server
}

std::vector<Shift> Server::retrieveShifts(void)
{
    std::vector<Shift> v(0);
    return v;   
}

}