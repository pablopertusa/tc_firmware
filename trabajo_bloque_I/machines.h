#pragma once
#include <iostream>
#include <map>
#include <string>

template <typename T>
class State;

template <typename T>
class Machine {
protected:
    std::map<std::string, State<T>> states;
    State<T>* currentState;

public:
    Machine() : currentState(nullptr) {
        std::cout << "-- creada instancia genérica de Machine" << std::endl;
    }
    
    virtual ~Machine() = default;

    void addState(std::string name, State<T> state) {
        states[name] = state;
    }

    virtual void setState(std::string stateName) {
        if (states.find(stateName) == states.end()) {
            std::cout << "ERROR: El estado " << stateName << " no existe." << std::endl;
            return;
        }

        if (currentState) {
            currentState->exit(this);
        }

        currentState = &states[stateName];
        currentState->enter(this);
    }

    virtual void transition(T input) {
        if (currentState) currentState->transition(this, input);
    }

    virtual void update() {
        if (currentState) currentState->update(this);
    }

    State<T>* getCurrentState() { return currentState; }
};

template <typename T>
class OperationalMachine : public Machine<T> {
private:
    float speed;
    float usage;

public:
    OperationalMachine() : speed(0.0f), usage(0.0f) {
        std::cout << "-- creada instancia de OperationalMachine" << std::endl;
    }

    float check_usage() { return usage; }
    float check_speed() { return speed; }
    void set_usage(float u) { usage = u; }
    void set_speed(float s) { speed = s; }
};