#include "concreteStates.h"
#include "machines.h"

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
    this->internalMachine = new OperationalMachine<char>();
}

void Operational::exit(PCUMachine *pcu) {
    std::cout << "Saliendo de Operational" << std::endl;
    delete this->internalMachine;
}

void Operational::transition(PCUMachine *pcu, char input) {
    if (this->internalMachine) {
        if (this->internalMachine->check_usage() >= 20) {
            pcu->setState(Fault::getInstance());
        }
        else {
            this->internalMachine->transition(input);
        }
    }
    else {
        std::cout << "ERROR: no hay internal machine en operational" << std::endl;
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

void Propulsion::enter(PCUMachine* op) {
    std::cout << "Entrando a Propulsion" << std::endl;
}

void Propulsion::exit(PCUMachine* op) {
    std::cout << "Saliendo de Propulsion" << std::endl;
}

void Propulsion::transition(PCUMachine* op, char input) {
    if (input == 'i') {
        op->setState(Idle::getInstance());
    }
    else if (input == 'b') {
        op->setState(Braking::getInstance());
    }
    else if (input == 'p') {
        op->setState(Propulsion::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

void Propulsion::update(PCUMachine* op) {
    std::cout << "Actualmente estamos en Propulsion" << std::endl;
    auto* opMachine = dynamic_cast<OperationalMachine<char>*>(op);

    if (opMachine) {
        opMachine->set_speed(opMachine->check_speed() + 5);
        opMachine->set_usage(opMachine->check_usage() + 2);
    }
    else {
        std::cout << "ERROR (propulsion): problema haciendo el cast" << std::endl;
    }
}

PCUState& Propulsion::getInstance() {
    static Propulsion singleton;
    return singleton;
}

void Idle::enter(PCUMachine* op) {
    std::cout << "Entrando a Idle" << std::endl;
}

void Idle::exit(PCUMachine* op) {
    std::cout << "Saliendo de Idle" << std::endl;
}

void Idle::transition(PCUMachine* op, char input) {
    if (input == 'i') {
        op->setState(Idle::getInstance());
    }
    else if (input == 'b') {
        op->setState(Braking::getInstance());
    }
    else if (input == 'p') {
        op->setState(Propulsion::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

void Idle::update(PCUMachine* op) {
    std::cout << "Actualmente estamos en Idle" << std::endl;
    auto *opMachine = dynamic_cast<OperationalMachine<char>*>(op); 
    if (opMachine) {
        if (opMachine->check_speed() > 0) {
            opMachine->set_speed(opMachine->check_speed() - 1);
        }
        opMachine->set_usage(opMachine->check_usage() + 1);
    }
    else {
        std::cout << "ERROR (idle): problema haciendo el cast" << std::endl;
    }
}

PCUState& Idle::getInstance() {
    static Idle singleton;
    return singleton;
}

void Braking::enter(PCUMachine* op) {
    std::cout << "Entrando a Braking" << std::endl;
}

void Braking::exit(PCUMachine* op) {
    std::cout << "Saliendo de Braking" << std::endl;
}

void Braking::transition(PCUMachine* op, char input) {
    if (input == 'i') {
        op->setState(Idle::getInstance());
    }
    else if (input == 'b') {
        op->setState(Braking::getInstance());
    }
    else if (input == 'p') {
        op->setState(Propulsion::getInstance());
    }
    else {
        std::cout << "Input no válido para el estado actual" << std::endl;
    }
}

void Braking::update(PCUMachine* op) {
    std::cout << "Actualmente estamos en Braking" << std::endl;
    auto *opMachine = dynamic_cast<OperationalMachine<char>*>(op); 
    if (opMachine) {
        opMachine->set_speed(opMachine->check_speed() - 5);
        if (opMachine->check_speed() < 0) {
            opMachine->set_speed(0.0);
        }
        opMachine->set_usage(opMachine->check_usage() + 3);
    }
    else {
        std::cout << "ERROR (braking): problema haciendo el cast" << std::endl;
    }
}

PCUState& Braking::getInstance() {
    static Braking singleton;
    return singleton;
}