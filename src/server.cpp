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

}