#include <iostream>

#include "client.hpp"

int main(int argc, char **argv)
{
    sv::Server server;
    cl::Client client{server};

    auto app = Gtk::Application::create("wkaelj.github.paymanager");

    app->run(client);
    
    return 0;
}