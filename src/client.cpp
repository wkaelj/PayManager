#include "client.hpp"


#include <algorithm>

namespace cl
{

Client::Client()
    : Gtk::Window(),
    server_(),
    internalPane_{Gtk::Orientation::HORIZONTAL}
{

    shifts_ = server_.retrieveShifts();
    shiftList_ = new ShiftList(shifts_, *this);
    shiftList_->updateShifts(shifts_);
    internalPane_.set_start_child(*shiftList_);

}

Client& Client::operator=(Client& cl)
{
    return cl;
}

void Client::addShift(sv::Shift s)
{
    shifts_.push_back(s);
    std::sort(shifts_.begin(), shifts_.end(), sv::Shift::compare);
    shiftList_->addShift(s);
}

void Client::deleteShift(sv::Shift s)
{

    if (shiftList_->deleteShift(s))
    {
        throw std::runtime_error("Client and List out of sync");
    }

    for (size_t i = 0; i < shifts_.size(); i++)
    {
        if (shifts_[i].date == s.date)
        {
            shifts_.erase(shifts_.begin() + i);
            return;
        }
    }

    throw std::runtime_error("Invalid shift attempting to erase. Client may be out of sync");
}

} // cl