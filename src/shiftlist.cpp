#include "shiftlist.hpp"

namespace cl
{

#include <string>
#include <time.h>

#include <stdexcept>

ShiftBox::ShiftBox(sv::Shift shift, Client &callback)
    : Gtk::Grid(),
    callback_{callback},
    shift_{shift},
    deleteButton_{createDeleteButton(*this)},
    editButton_{createEditButton(*this)}
{
    // date label
    std::string dateString = asctime(gmtime(&shift_.date));
    Gtk::Label date{dateString};
    add(date);

    // duration label
    std::string durationString;
    durationString.append(std::to_string(shift_.duration / 60)).append("h, "); // hours
    durationString.append(std::to_string(shift_.duration % 60)).append("m"); // minutes

    Gtk::Label duration{durationString};
    add(duration);

}

Gtk::Button ShiftBox::createDeleteButton(ShiftBox &self)
{

    Gtk::Button deleteButton{"Delete"};
    deleteButton.set_always_show_image(true);
    deleteButton.set_image_from_icon_name("edit-delete", Gtk::ICON_SIZE_BUTTON);
    deleteButton.signal_clicked().connect(
        sigc::mem_fun(self, &ShiftBox::delete_callback));
    
    return deleteButton;
}

Gtk::Button ShiftBox::createEditButton(ShiftBox &self)
{
    Gtk::Button editButton{"Edit"};
    editButton.set_always_show_image(true);
    editButton.set_image_from_icon_name("edit-entry", Gtk::ICON_SIZE_BUTTON);
    editButton.signal_clicked().connect(
        sigc::mem_fun(self, &ShiftBox::edit_callback));

    return editButton;
}

ShiftBox& ShiftBox::operator = (ShiftBox& other)
{

    callback_ = other.callback_;
    shift_ = other.shift_;
    deleteButton_ = createDeleteButton(*this);
    editButton_ = createEditButton(*this);


    return *this;
}

ShiftBox::~ShiftBox()
{
    
}

void ShiftBox::delete_callback()
{
    callback_.deleteShift(shift_);
}

ShiftList::ShiftList(std::vector<sv::Shift> &shifts, Client &cl)
    : Gtk::ScrolledWindow{},
    callback_{cl},
    internalViewport_{
        Gtk::ScrolledWindow::get_vadjustment(), 
        Gtk::ScrolledWindow::get_vadjustment()}
{

    internalGrid_.set_row_homogeneous(true);

    internalViewport_.add(internalGrid_);
    updateShifts(shifts);
}

void ShiftList::updateShifts(std::vector<sv::Shift> &shifts)
{

    // delete all children
    for (std::size_t i = 0; i < listBoxes_.size(); i++)
    {
        internalGrid_.remove(listBoxes_[i]);
        listBoxes_.erase(listBoxes_.begin() + i);
    }
    
    for (sv::Shift s : shifts)
    {
        addShift(s);
    }
}

void ShiftList::addShift(sv::Shift s)
{
    
    // iterate through list
        // if shift at date already exists, overwrite
        // otherwise, insert the shift if it belongs
    // otherwise insert new shift at the end of list

    // check if shift should be further ahead in list
    for (size_t i = 0; i < listBoxes_.size(); i++)
    {
        // replace
        if (listBoxes_[i].getDate() == s.date)
        {
            listBoxes_.assign(i, {s, callback_});
            internalGrid_.attach(listBoxes_[i], 0, i, 1, 1);
            return;
        } else if (listBoxes_[i].getDate() < s.date) // insert behind
        {
            listBoxes_.insert(listBoxes_.begin() + i, {s, callback_});
            internalGrid_.insert_row(i);
            internalGrid_.attach(listBoxes_[i], 0, i, 1, 1);
            return;
        }

        internalGrid_.insert_row(listBoxes_.size());
        listBoxes_.push_back({s, callback_});
        internalGrid_.attach(listBoxes_[listBoxes_.size()], 0, listBoxes_.size(), 1, 1);
    }

    return;
}

bool ShiftList::deleteShift(sv::Shift s)
{
    return deleteShift(s.date);
}

bool ShiftList::deleteShift(time_t date)
{

    for (size_t i = 0; i < listBoxes_.size(); i++)
    {
        if (listBoxes_[i].getDate() == date)
        {
            internalGrid_.remove(listBoxes_[i]);
            internalGrid_.remove_row(i);
            listBoxes_.erase(listBoxes_.begin() + i);
            return true;
        }
    }

    return false;
}

} // cl
