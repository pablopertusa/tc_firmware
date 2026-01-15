#include "machines.h"
#include "concreteStates.h"

PCUMachine::PCUMachine() {
    std::cout << "creada instancia de PCUMachine" << std::endl;
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

OperationalMachine::OperationalMachine() {
    std::cout << "creada instancia de PCUMachine" << std::endl;
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