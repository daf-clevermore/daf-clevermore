#include <iostream>
#include <memory>
#include <vector>


class Vehicle {
public:
Vehicle(int speed) : maxSpeed(speed) {}
virtual ~Vehicle() = default;
virtual void move() const = 0;
protected:
int maxSpeed;
};


class Car : public Vehicle {
public:
Car(int speed) : Vehicle(speed) {}
void move() const override {
std::cout << "Mobil melaju hingga " << maxSpeed << " km/h\n";
}
};


class Motorcycle : public Vehicle {
public:
Motorcycle(int speed) : Vehicle(speed) {}
void move() const override {
std::cout << "Sepeda motor melaju sampai " << maxSpeed << " km/h\n";
}
};


int main() {
std::vector<std::unique_ptr<Vehicle>> v;
v.push_back(std::make_unique<Car>(120));
v.push_back(std::make_unique<Motorcycle>(80));


for (const auto &veh : v) veh->move();
}