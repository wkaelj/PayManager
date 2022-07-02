#include "server.hpp"

namespace sv
{

bool Shift::compare(Shift a, Shift b)
{
    return a.date > b.date;
}

Server::Server()
{
    // idk what to do yet
}

Server::~Server()
{
    // save data
}

std::vector<Shift> Server::retrieveShifts(void)
{
    std::vector<Shift> v(0);
    return v;
}

}