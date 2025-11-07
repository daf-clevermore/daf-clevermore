#include <iostream>
#include <memory>
#include <vector>
#include <string>


class Animal {
public:
Animal(std::string n): name(std::move(n)) {}
virtual ~Animal() = default;
virtual void sound() const = 0;
protected:
std::string name;
};


class Dog : public Animal {
public:
using Animal::Animal;
void sound() const override { std::cout << name << ": Gukguk!\n"; }
};


class Cat : public Animal {
public:
using Animal::Animal;
void sound() const override { std::cout << name << ": Meow~\n"; }
};


int main() {
std::vector<std::unique_ptr<Animal>> zoo;
zoo.push_back(std::make_unique<Dog>("Dog"));
zoo.push_back(std::make_unique<Cat>("Cat"));


for (const auto &a : zoo) a->sound();
}