#pragma once
#include "states.h"
#include "machines.h"
#include <iostream>

using PCUState = State<char>;
using PCUMachine = Machine<char>;

class Connecting : public PCUState {
public:
    void enter(PCUMachine* pcu) override;
    void exit(PCUMachine* pcu) override;
    void transition(PCUMachine* pcu, char input) override;
    void update(PCUMachine* pcu) override;
    static PCUState& getInstance();

private:
    Connecting() { std::cout << "-- creada instancia de Connecting" << std::endl; }
};

class Operational : public PCUState {
public:
    void enter(PCUMachine* pcu) override;
    void exit(PCUMachine* pcu) override;
    void transition(PCUMachine* pcu, char input) override;
    void update(PCUMachine* pcu) override;
    static PCUState& getInstance();

private:
    Operational() { std::cout << "-- creada instancia de Operational" << std::endl; }
    OperationalMachine<char>* internalMachine;
};

class Fault : public PCUState {
public:
    void enter(PCUMachine* pcu) override;
    void exit(PCUMachine* pcu) override;
    void transition(PCUMachine* pcu, char input) override;
    void update(PCUMachine* pcu) override;
    static PCUState& getInstance();

private:
    Fault() { std::cout << "-- creada instancia de Fault" << std::endl; }
};

class Idle : public PCUState {
public:
    void enter(PCUMachine* pcu) override;
    void exit(PCUMachine* pcu) override;
    void transition(PCUMachine* pcu, char input) override;
    void update(PCUMachine* pcu) override;
    static PCUState& getInstance();

private:
    Idle() { std::cout << "-- creada instancia de Idle" << std::endl; }
};

class Propulsion : public PCUState {
public:
    void enter(PCUMachine* pcu) override;
    void exit(PCUMachine* pcu) override;
    void transition(PCUMachine* pcu, char input) override;
    void update(PCUMachine* pcu) override;
    static PCUState& getInstance();

private:
    Propulsion() { std::cout << "-- creada instancia de Propulsion" << std::endl; }
};

class Braking : public PCUState {
public:
    void enter(PCUMachine* pcu) override;
    void exit(PCUMachine* pcu) override;
    void transition(PCUMachine* pcu, char input) override;
    void update(PCUMachine* pcu) override;
    static PCUState& getInstance();

private:
    Braking() { std::cout << "-- creada instancia de Braking" << std::endl; }
};