#include "concreteStates.h"
#include "machines.h"
#include "states.h"

void Connecting::enter(PCUMachine *pcu) {
    std::cout << "Entrando a connecting" << std::endl;
}

void Connecting::exit(PCUMachine *pcu) {
    std::cout << "Saliendo de connecting" << std::endl;
}

void Connecting::transition(PCUMachine *pcu, char input) {
    if (input == 'o') {
        pcu->setState(Operational::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

PCUState& Connecting::getInstance() {
    static Connecting singleton;
    return singleton;
}

void Connecting::update(PCUMachine *pcu) {
    std::cout << "Actualmente estamos en Connecting" << std::endl;
}

void Fault::enter(PCUMachine *pcu) {
    std::cout << "Entrando a Fault" << std::endl;
}

void Fault::exit(PCUMachine *pcu) {
    std::cout << "Saliendo de Fault" << std::endl;
}

void Fault::transition(PCUMachine *pcu, char input) {
    if (input == 'r') {
        pcu->setState(Connecting::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

PCUState& Fault::getInstance() {
    static Fault singleton;
    return singleton;
}

void Fault::update(PCUMachine *pcu) {
    std::cout << "Actualmente estamos en Fault" << std::endl;
}

void Operational::enter(PCUMachine *pcu) {
    std::cout << "Entrando a Operational" << std::endl;
    this->internalMachine = new OperationalMachine();
}

void Operational::exit(PCUMachine *pcu) {
    std::cout << "Saliendo de Operational" << std::endl;
    delete this->internalMachine;
}

void Operational::transition(PCUMachine *pcu, char input) {
    this->internalMachine->transition(input);

    // si se ha usado mucho se rompe
    if (this->internalMachine->check_usage() >= 20) {
        pcu->setState(Fault::getInstance());
    }
}

PCUState& Operational::getInstance() {
    static Operational singleton;
    return singleton;
}

void Operational::update(PCUMachine *pcu) {
    this->internalMachine->update();
    std::cout << "- Velocidad = " << this->internalMachine->check_speed() << std::endl;
    std::cout << "- Uso = " << this->internalMachine->check_usage() << std::endl;
}

void Propulsion::enter(OperationalMachine* op) {
    std::cout << "Entrando a Propulsion" << std::endl;
}

void Propulsion::exit(OperationalMachine* op) {
    std::cout << "Saliendo de Propulsion" << std::endl;
}

void Propulsion::transition(OperationalMachine* op, char input) {
    if (input == 'i') {
        op->setState(Idle::getInstance());
    }
    else if (input == 'b') {
        op->setState(Braking::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

void Propulsion::update(OperationalMachine* op) {
    std::cout << "Actualmente estamos en Propulsion" << std::endl;
    op->set_speed(op->check_speed() + 5);
    op->set_usage(op->check_usage() + 2);
}

OperationalState& Propulsion::getInstance() {
    static Propulsion singleton;
    return singleton;
}

void Idle::enter(OperationalMachine* op) {
    std::cout << "Entrando a Idle" << std::endl;
}

void Idle::exit(OperationalMachine* op) {
    std::cout << "Saliendo de Idle" << std::endl;
}

void Idle::transition(OperationalMachine* op, char input) {
    if (input == 'p') {
        op->setState(Propulsion::getInstance());
    }
    else if (input == 'b') {
        op->setState(Braking::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

void Idle::update(OperationalMachine* op) {
    std::cout << "Actualmente estamos en Idle" << std::endl;
    if (op->check_speed() > 0) {
        op->set_speed(op->check_speed() - 1);
    }
    op->set_usage(op->check_usage() + 1);
}

OperationalState& Idle::getInstance() {
    static Idle singleton;
    return singleton;
}

void Braking::enter(OperationalMachine* op) {
    std::cout << "Entrando a Braking" << std::endl;
}

void Braking::exit(OperationalMachine* op) {
    std::cout << "Saliendo de Braking" << std::endl;
}

void Braking::transition(OperationalMachine* op, char input) {
    if (input == 'p') {
        op->setState(Propulsion::getInstance());
    }
    else if (input == 'i') {
        op->setState(Idle::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

void Braking::update(OperationalMachine* op) {
    std::cout << "Actualmente estamos en Braking" << std::endl;
    op->set_speed(op->check_speed() - 5);
    if (op->check_speed() < 0) {
        op->set_speed(0.0);
    }
    op->set_usage(op->check_usage() + 3);
}

OperationalState& Braking::getInstance() {
    static Braking singleton;
    return singleton;
}