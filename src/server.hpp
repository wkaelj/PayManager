#ifndef SV_SERVER_H
#define SV_SERVER_H

#include <vector>
#include <time.h>


namespace sv
{

// store the data regarding a shift
// no two shifts can have the same date
// shifts can overlap (but they shouldn't)
struct Shift
{
    time_t date; // the time you started the shift (unix time)
    time_t duration; // time duration of the shift (seconds)

    static bool compare(Shift a, Shift b);
};

// manage the storage of the data
class Server
{
    public:
    Server();
    ~Server();

    // save the shifts to the server
    void saveShifts(std::vector<Shift> shifts);
    std::vector<Shift> retrieveShifts();

    private:
    int serverIP_;
    
};

}

#endif // SV_SERVER_H