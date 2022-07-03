#ifndef CL_SHIFT_LIST_H
#define CL_SHIFT_LIST_H

#include "client.hpp"

namespace cl
{

class Client;


class ShiftBox
{

    public:
    ShiftBox(sv::Shift shift, Client &callback);
    time_t getDate(void) { return shift_.date; }
    time_t getDuration(void) { return shift_.duration; }

    // copy operator
    ShiftBox(const ShiftBox &other);
    ShiftBox& operator = (const ShiftBox &other);

    static ShiftBox create(sv::Shift s, Client &callback);

    private:
    Client &callback_;

    sv::Shift shift_;

    // gtk components
    Gtk::Grid internalGrid_;
    Gtk::Button deleteButton_;
    static Gtk::Button createDeleteButton(ShiftBox &self);
    Gtk::Button editButton_;
    static Gtk::Button createEditButton(ShiftBox &self);

    // gtk callbacks
    void delete_callback(void);
    void edit_callback(void);

};

class ShiftList : public Gtk::ScrolledWindow
{

    public:
    ShiftList(std::vector<sv::Shift> &shifts, Client &callback);

    // get the list of shifts
    std::vector<sv::Shift> &getShiftList(void);

    // reload all shifts
    void updateShifts(std::vector<sv::Shift> &shifts);
    void addShift(sv::Shift s);

    bool deleteShift(sv::Shift s);
    bool deleteShift(time_t date);

    // Update references
    void setShiftReference(std::vector<sv::Shift> &reference);

    private:
    // settings
    const int boxSpacing_ = 8;

    Client &callback_;

    Gtk::Viewport internalViewport_; // contain grid widgets
    Gtk::Grid      internalGrid_;
    std::vector<ShiftBox> listBoxes_;

};

} // cl

#endif // CL_SHIFT_LIST_H