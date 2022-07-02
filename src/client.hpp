#ifndef CL_CLIENT_H
#define CL_CLIENT_H

#include <vector>
#include <gtkmm.h>

#include "server.hpp"

#include "shiftlist.hpp"

namespace cl
{

class ShiftList;

// manage the GUI
// - Add a new shift
// - retrieve shifts from server
// - send shifts to server
class Client : public Gtk::Window
{

    public:
    Client(sv::Server &server);
    ~Client();

    void addShift(sv::Shift s);
    void deleteShift(sv::Shift s);

    // assignment operator
    Client& operator = (Client& cl);

    private:
    std::vector<sv::Shift> shifts_;

    sv::Server &server_;
    
    ShiftList *shiftList_;

    // gtk components
    Gtk::Paned internalPane_;
};

} // cl

#endif // CL_CLIENT_H