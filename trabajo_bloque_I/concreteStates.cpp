#include "concreteStates.h"
#include "machines.h"

void Connecting::enter(PCUMachine *pcu) {
}

void Connecting::exit(PCUMachine *pcu) {
}

void Connecting::transition(PCUMachine *pcu, char input) {
    // definir siguiente y actualizarlo
    // if input == "x"; pcu->currentState = newState;
}

PCUState& Connecting::getInstance() {
    static Connecting singleton;
    return singleton;
}

void Fault::enter(PCUMachine *pcu) {
}

void Fault::exit(PCUMachine *pcu) {
}

void Fault::transition(PCUMachine *pcu, char input) {
}