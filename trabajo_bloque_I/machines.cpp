#include "machines.h"
#include "states.h"
#include "concreteStates.h"

template <typename T>
Machine<T>::Machine() : currentState(nullptr) {
    std::cout << "-- creada instancia de PCUMachine" << std::endl;
    this->currentState = &Connecting::getInstance();
}

template <typename T>
OperationalMachine<T>::OperationalMachine() {
    std::cout << "-- creada instancia de OperationalMachine" << std::endl;
    this->speed = 0.0f;
    this->usage = 0.0f;
    this->currentState = &Idle::getInstance();
}

template class Machine<char>;
template class OperationalMachine<char>;