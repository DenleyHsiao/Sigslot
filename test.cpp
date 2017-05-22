#include <iostream>
#include "sigslot.h"

using namespace sigslot;


int main(int argc, const char * argv[]) {
    class Car : public has_slots<>
    {
    public:
        void OnSpeedChange(double mph) {
            std::cout << "Speed changed to " << mph << "\n";
        }
        void OnBrakesApplied(bool brakestate, bool hard) {
            std::cout << ( brakestate ? "" : "not " ) << "braking" << ( hard ? " hard" : "" ) << "\n";
        }
    };

    Car car;
    signal1<double> Speed;
    signal2<bool, bool> Brakes;
    Speed.connect(&car, &Car::OnSpeedChange);
    Brakes.connect(&car, &Car::OnBrakesApplied);
    Speed(50.0); // This one gets through
    Brakes(true, false); // So does this
    Brakes(false, false); // So does this
    Brakes(true, true); // So does this

    car.disconnect_all();

    Speed(31.5); // This one doesn’t get through

    return 0;
}
