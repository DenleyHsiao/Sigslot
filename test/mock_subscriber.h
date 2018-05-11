#ifndef __TEST_UTIL__
#define __TEST_UTIL__

#include "sigslot.h"
#include <sstream>
#include <string>

class MockSubscriber : public sigslot::has_slots<>
{
public:
    MockSubscriber() : data("") {}
    template <typename T, typename... Args>
    void update(T value, Args... args) {
        std::stringstream ss;
        ss << value;
        data += ss.str();
        if ((sizeof...(args) > 0)) update(args...);
    }
    void update() {
        data = "";
    }
    const char* result() const {
        return data.c_str();
    }
private:
    std::string data;
};

#endif