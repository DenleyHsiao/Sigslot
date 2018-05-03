#include "sigslot.h"
#include <sstream>
#include <cassert>

using namespace sigslot;

class Car : public has_slots<>
{
public:
    Car() : value("") {}
    void OnSpeedChange(double mph) {
        std::stringstream ss;
        ss << "Speed changed to " << mph << "\n";
        value = ss.str();
    }
    void OnBrakesApplied(bool brakestate, bool hard) {
        std::stringstream ss;
        ss << ( brakestate ? "" : "not " ) << "braking" << ( hard ? " hard" : "" ) << "\n";
        value = ss.str();
    }
public:
    std::string value;
};

void test() {
    Car car;
    signal1<double> Speed;
    signal2<bool, bool> Brakes;
    Speed.connect(&car, &Car::OnSpeedChange);
    Brakes.connect(&car, &Car::OnBrakesApplied);

    Speed(50.0);
    assert(car.value == "Speed changed to 50\n");
    Brakes(true, false);
    assert(car.value == "braking\n");
    Brakes(false, false);
    assert(car.value == "not braking\n");
    Brakes(true, true);
    assert(car.value == "braking hard\n");

    car.disconnect_all();

    Speed(31.5); // This one doesn’t get through
    assert(car.value != "Speed changed to 31.5\n");
}

int main(int argc, const char * argv[]) {
    test();

    return 0;
}
