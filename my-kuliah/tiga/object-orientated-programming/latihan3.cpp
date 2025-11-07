#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Transport {
public:
    Transport(int c) : capacity(c) {}
    virtual ~Transport() = default;

    virtual void startRoute() const = 0;
    virtual int getFare() const = 0;

protected:
    int capacity;
};

class Bus : public Transport {
public:
    Bus(int c, int f) : Transport(c), fare(f) {}

    void startRoute() const override {
        std::cout << "Bus TransJakarta berangkat dengan kapasitas " << capacity << " penumpang.\n";
    }

    int getFare() const override {
        return fare;
    }

private:
    int fare;
};

class Train : public Transport {
public:
    Train(int c, int f) : Transport(c), fare(f) {}

    void startRoute() const override {
        std::cout << "KRL berjalan dengan kapasitas " << capacity << " penumpang.\n";
    }

    int getFare() const override {
        return fare;
    }

private:
    int fare;
};

class OnlineRide : public Transport {
public:
    OnlineRide(int surgeMultiplier) 
        : Transport(1), multiplier(surgeMultiplier) {}

    void startRoute() const override {
        std::cout << "Ojek Online menjemput 1 penumpang.\n";
    }

    int getFare() const override {
        return baseFare * multiplier;
    }

private:
    int baseFare = 10000;
    int multiplier;
};

int main() {
    std::vector<std::unique_ptr<Transport>> list;

    list.push_back(std::make_unique<Bus>(40, 3500));
    list.push_back(std::make_unique<Train>(200, 8000));
    list.push_back(std::make_unique<OnlineRide>(2));

    for (const auto &t : list) {
        t->startRoute();
        std::cout << "Tarif: " << t->getFare() << "\n\n";
    }

    return 0;
}
