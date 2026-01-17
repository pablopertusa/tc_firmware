#include "machines.h"
#include "concreteStates.h"

PCUMachine::PCUMachine() {
    std::cout << "-- creada instancia de PCUMachine" << std::endl;
    this->currentState = &Connecting::getInstance();
}

PCUState* PCUMachine::getCurrentState() {
    return this->currentState;
}

void PCUMachine::transition(char input) {
    currentState->transition(this, input);
}

void PCUMachine::setState(PCUState &newState) {
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

void PCUMachine::update() {
    this->currentState->update(this);
}

OperationalMachine::OperationalMachine() {
    std::cout << "-- creada instancia de OperationalMachine" << std::endl;
    this->currentState = &Idle::getInstance();
}

OperationalState* OperationalMachine::getCurrentState() {
    return this->currentState;
}

void OperationalMachine::transition(char input) {
    currentState->transition(this, input);
}

void OperationalMachine::setState(OperationalState &newState) {
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

float OperationalMachine::check_speed() {
    return this->speed;
}

float OperationalMachine::check_usage() {
    return this->usage;
}

void OperationalMachine::set_speed(float s) {
    this->speed = s;
}

void OperationalMachine::set_usage(float u) {
    this->usage = u;
}

void OperationalMachine::update() {
    this->currentState->update(this);
}