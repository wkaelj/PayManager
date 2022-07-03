#include <iostream>

// #include "client.hpp"
#include <gtkmm.h>

int main(int argc, char **argv)
{

    auto app = Gtk::Application::create("wkaelj.github.paymanager");

    app->make_window_and_run<Gtk::Window>(argc, argv);
    
    return 0;
}