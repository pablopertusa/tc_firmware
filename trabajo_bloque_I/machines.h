#pragma once

#include <iostream>

template <typename T>
class State;

template <typename T>
class Machine {
protected:
    State<T>* currentState;
public:
    Machine(); 
    virtual ~Machine() = default;

    virtual void setState(State<T>& newState) {
        if (currentState) {
            currentState->exit(this);
        }
        else {
            std::cout << "ERROR: no hay estado actual" << std::endl;
        }
        currentState = &newState;
        currentState->enter(this);
    }

    virtual void transition(T input) {
        if (currentState) {
            currentState->transition(this, input);
        }
        else {
            std::cout << "ERROR: no hay estado actual" << std::endl;
        }
    }

    virtual void update() {
        if (currentState) {
            currentState->update(this);
        }
        else {
            std::cout << "ERROR: no hay estado actual" << std::endl;
        }
    }

    virtual State<T>* getCurrentState() {
        return currentState;
    }
};

template <typename T>
class OperationalMachine : public Machine<T> {
private:
    float speed;
    float usage;

public:
    OperationalMachine();

    float check_usage() { return usage; }
    float check_speed() { return speed; }
    void set_usage(float u) { usage = u; }
    void set_speed(float s) { speed = s; }
};